#include <fstream>
#include <iostream>
#include "ast/all.hh"
#include "compiler.hh"
#include <cassert>

namespace compile {

    void Compile::process(ast::Ast& a)
    {
        operator()(a);
        emitter_.emit<OP_HALT>();
        for (auto e : dec_)
        {
            e->function_offset_set(emitter_.get_current_length());
            for (long i = e->params_get().size() - 1; i >= 0; i--)
                emitter_.emit<OP_POPR, int16_t>(e->params_get()[i].number_get());
            e->body_get()->set_used(e->return_t_get() != nullptr);
            e->body_get()->accept(*this);

            if (e->body_get()->is_used())
                emitter_.emit<OP_POPR, int16_t>(0);
            emitter_.emit<OP_RET>();
        }
    }

    void Compile::operator()(ast::Ast& a) {
        ast::Exp* e = dynamic_cast<ast::Exp*>(&a);
        if (e != nullptr)
            e->set_used(true);
        super::operator()(a);
    }

    template <Bytecode T>
    void Compile::emit_cmp() {
        long first_address = emitter_.emit<T, int16_t>();
        long first_size = emitter_.get_current_length();

        emitter_.emit<OP_PUSH, int64_t>(0);

        long jmp_address = emitter_.emit<OP_JMP, int16_t>();
        long jmp_size = emitter_.get_current_length();
        emitter_.buf_get()[first_address].add_operand<int16_t>(jmp_size - first_size);

        emitter_.emit<OP_PUSH, int64_t>(1);
        emitter_.buf_get()[jmp_address].add_operand<int16_t>(emitter_.get_current_length() - jmp_size);

    }

    void Compile::operator()(ast::BinaryExp& e) {
        e.valuel_get()->set_used(true);
        e.expr_get()->set_used(true);
        super::operator()(e);
        if (!e.is_used()) { //Assert that binaryop does not have sid effet
            emitter_.emit<OP_POP>();
            emitter_.emit<OP_POP>();
            return;
        }
        switch (e.op_get()) {
            //TODO: more ops
            case ast::PLUS:  emitter_.emit<OP_ADD>(); break;
            case ast::MINUS: emitter_.emit<OP_SUB>(); break;
            case ast::MUL:   emitter_.emit<OP_MUL>(); break;
            case ast::DIV:   emitter_.emit<OP_DIV>(); break;
            case ast::MOD:   emitter_.emit<OP_MOD>(); break;
            case ast::AND:   emitter_.emit<OP_AND>(); break;
            case ast::OR:   emitter_.emit<OP_OR>(); break;
            case ast::XOR:   emitter_.emit<OP_XOR>(); break;
            case ast::EQUAL:  emit_cmp<OP_JE>(); break;
            case ast::NEQUAL:  emit_cmp<OP_JNE>(); break;
            case ast::GREATER:  emit_cmp<OP_JG>(); break;
            case ast::GREATER_EQ:  emit_cmp<OP_JGE>(); break;
            case ast::LESS:  emit_cmp<OP_JL>(); break;
            case ast::LESS_EQ:  emit_cmp<OP_JLE>(); break;
            default: break;
        };
    }

    void Compile::operator()(ast::Lvalue &e) {
        super::operator()(e);
        std::shared_ptr<ast::Declaration> decl = e.s_get()->dec_get();

        if (std::shared_ptr<ast::VarDec> vardec = std::dynamic_pointer_cast<ast::VarDec>(decl)) {
            if (e.is_used())
                emitter_.emit<OP_PUSHR, uint16_t>(vardec->number_get());
            else
                return;
        } else {
            std::cerr << "Could not resolve symbol";
            // TODO: proper error handling, should not happend
        }
    }

    void Compile::operator()(ast::VarDec &e) {
        super ::operator()(e);

        emitter_.emit<OP_PUSH, int64_t>(0);
        emitter_.emit<OP_POPR, int16_t>(e.number_get());
        if (e.is_used()) {
            emitter_.emit<OP_PUSH, uint64_t>(0);
        }
    }

    void Compile::assign_register(ast::Lvalue& e, ast::AssignExp& a)
    {
        a.exp_get()->set_used(true);
        super::operator()(*a.exp_get());

        std::shared_ptr<ast::Declaration> decl = e.s_get()->dec_get();

        if (std::shared_ptr<ast::VarDec> vardec = std::dynamic_pointer_cast<ast::VarDec>(decl)) {
            emitter_.emit<OP_POPR, uint16_t>(vardec->number_get());
            if (a.is_used()) //should never happend
                emitter_.emit<OP_PUSHR, uint16_t>(vardec->number_get());
        }
    }

    void Compile::assign_struct(ast::MemberAccess& e, ast::AssignExp& a)
    {
        e.lval_get()->set_used(true);
        e.lval_get()->accept(*this);
        //FIXME actually O(n), need to fix it
        for (unsigned i = 0; i < e.def_get()->members_get().size(); i++) {
            auto& v = e.def_get()->members_get()[i];
            if (v.name_get()->s_get() == e.s_get()->s_get()) {
                emitter_.emit<OP_PUSH, int64_t>(i);
                break;
            }
        }

        a.exp_get()->set_used(true);
        a.exp_get()->accept(*this);

        emitter_.emit<OP_WRITE>();

        assert(!e.is_used());
    }

    void Compile::assign_array(ast::ArrayAccess& e, ast::AssignExp& a)
    {
        e.val_get()->set_used(true);
        e.val_get()->accept(*this);

        e.offset_get()->set_used(true);
        e.offset_get()->accept(*this);

        a.exp_get()->set_used(true);
        a.exp_get()->accept(*this);

        emitter_.emit<OP_WRITE>();

        assert(!e.is_used());
    }

    void Compile::operator()(ast::AssignExp &e) {

        std::shared_ptr<ast::ArrayAccess> arr = std::dynamic_pointer_cast<ast::ArrayAccess>(e.lvalue_get());
        if (arr)
        {
            assign_array(*arr, e);
            return;
        }

        std::shared_ptr<ast::MemberAccess> memb = std::dynamic_pointer_cast<ast::MemberAccess>(e.lvalue_get());
        if (memb)
        {
            assign_struct(*memb, e);
            return;
        }

        std::shared_ptr<ast::Lvalue> lval = std::dynamic_pointer_cast<ast::Lvalue>(e.lvalue_get());
        if (lval)
        {
            assign_register(*lval, e);
            return;
        }

    }

    void Compile::operator()(ast::Int& e) {
        if (e.is_used())
            emitter_.emit<OP_PUSH, uint64_t>(e.value_get());
    }

    void Compile::operator()(ast::DoExp& e) {
        if (e.is_used())
            emitter_.emit<OP_PUSH, uint64_t>(0);
        long do_instruction = emitter_.get_current_length();
        if (e.is_used())
            emitter_.emit<OP_POP>();

        e.body_get()->set_used(e.is_used());
        e.body_get()->accept(*this);

        e.condition_get()->set_used(true);
        e.condition_get()->accept(*this);

        emitter_.emit<OP_PUSH, uint64_t>(0);
        emitter_.emit<OP_JNE, int16_t>();

        long jmp_instruction = emitter_.get_current_length();

        //Set jump to the start of the do
        emitter_.buf_get()[emitter_.buf_get().size() - 1].add_operand<int16_t>(do_instruction - jmp_instruction);
    }

    void Compile::operator()(ast::ExpList& e) {
        auto b = e.list_get().begin();
        auto end = e.list_get().end();
        while (b != end)
        {
            if (b + 1 == end)
                (*b)->set_used(e.is_used());
            (*b)->accept(*this);
            ++b;
        }
    }

    void Compile::operator()(ast::ExpListInner& e) {
        auto b = e.list_get().begin();
        auto end = e.list_get().end();
        while (b != end)
        {
            if (b + 1 == end)
                (*b)->set_used(e.is_used());
            (*b)->accept(*this);
            ++b;
        }
    }

    void Compile::operator()(ast::ForExp& e) {
        if (e.init_get())
            e.init_get()->accept(*this);

        long jmp_address = emitter_.emit<OP_JMP, int16_t>();
        long jmp_instruction = emitter_.get_current_length();
        long body_instruction = emitter_.get_current_length();

        e.body_get()->set_used(e.is_used());
        e.body_get()->accept(*this);

        if (e.end_get())
            e.end_get()->accept(*this);

        long cond_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].add_operand<int16_t>(cond_instruction - jmp_instruction);

        e.condition_get()->set_used(true);
        e.condition_get()->accept(*this);

        emitter_.emit<OP_PUSH, uint64_t>(0);
        emitter_.emit<OP_JNE, int16_t>();

        cond_instruction = emitter_.get_current_length();

        emitter_.buf_get()[emitter_.buf_get().size() - 1].add_operand<int16_t>( - (cond_instruction - body_instruction));

    }

    void Compile::operator()(ast::IfExp& e) {
        e.if_get()->set_used(true);
        e.if_get()->accept(*this);

        emitter_.emit<OP_PUSH, uint64_t>(0);

        long jmp_address = emitter_.emit<OP_JE, int16_t>();
        long jmp_instruction = emitter_.get_current_length();

        e.then_get()->set_used(e.is_used());
        e.then_get()->accept(*this);

        long then_adress = emitter_.emit<OP_JMP, int16_t>();
        long then_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].add_operand<int16_t>(then_instruction - jmp_instruction);

        e.else_get()->set_used(e.is_used());
        e.else_get()->accept(*this);
        emitter_.buf_get()[then_adress].add_operand<int16_t>(emitter_.get_current_length() - then_instruction);
    }

    void Compile::operator()(ast::UnaryExp& e) {
        e.exp_get()->set_used(true);
        switch (e.op_get()) {
            //TODO: more ops
            case ast::PLUS:  break; // WHAT ?
            case ast::TILDE:  break; // WHAT ?
            case ast::MINUS:
                              emitter_.emit<OP_PUSH, int64_t>(0);
                              e.exp_get()->accept(*this);
                              emitter_.emit<OP_SUB>(); break;
            case ast::BANG:
                              e.exp_get()->accept(*this);
                              emitter_.emit<OP_NOT>(); break;
            default: break;
        };
        if (!e.is_used()) { //Assert that op does not have sid effet
            emitter_.emit<OP_POP>();
            return;
        }
    }

    void Compile::operator()(ast::WhileExp& e) {
        long jmp_address = emitter_.emit<OP_JMP, int16_t>();
        long body_instruction = emitter_.get_current_length();
        e.body_get()->set_used(e.is_used());
        e.body_get()->accept(*this);
        long cond_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].add_operand<int16_t>(cond_instruction - body_instruction);
        e.condition_get()->set_used(true);
        e.condition_get()->accept(*this);

        emitter_.emit<OP_PUSH, int64_t>(0);
        jmp_address = emitter_.emit<OP_JNE, int16_t>();

        cond_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].add_operand<int16_t>( - (cond_instruction - body_instruction));
    }

    void Compile::operator()(ast::ExpListFunction& e) {
        auto b = e.list_get().begin();
        auto end = e.list_get().end();
        while (b != end) {
            (*b)->set_used(true);
            (*b)->accept(*this);
            ++b;
        }
    }

    void Compile::operator()(ast::VarAssign& e) {


        e.value_get()->set_used(true);
        e.value_get()->accept(*this);

        emitter_.emit<OP_POPR, int16_t>(e.number_get());
        if (e.is_used()) //should never happend
            emitter_.emit<OP_PUSHR, int16_t>(e.number_get());
    }

    void Compile::operator()(ast::FunCall& e) {
        emitter_.emit<OP_SAVE,uint16_t>(e.func_get()->number_get());
        e.list_get()->accept(*this);
        emitter_.emit<OP_CALL,uint16_t>(e.func_get()->number_get());
        emitter_.emit<OP_RESTORE,uint16_t>(e.func_get()->number_get());
        if (e.is_used())
        {
            emitter_.emit<OP_PUSHR, int16_t>(0);
        }
    }

    void Compile::operator()(ast::FunctionDec& e) {
        //Everything is ok;
    }

    void Compile::operator()(ast::MemberAccess& e) {
        e.lval_get()->set_used(true);
        e.lval_get()->accept(*this);
        //FIXME actually O(n), need to fix it
        for (unsigned i = 0; i < e.def_get()->members_get().size(); i++) {
            auto& v = e.def_get()->members_get()[i];
            if (v.name_get()->s_get() == e.s_get()->s_get()) {
                emitter_.emit<OP_PUSH, int64_t>(i);
                break;
            }
        }
        emitter_.emit<OP_READ>();
        if (!e.is_used())
            emitter_.emit<OP_POP>();
    }

    void Compile::operator()(ast::ArrayAccess& e) {
        e.val_get()->set_used(true);
        e.val_get()->accept(*this);
        e.offset_get()->set_used(true);
        e.offset_get()->accept(*this);
        emitter_.emit<OP_READ>();
        if (!e.is_used())
            emitter_.emit<OP_POP>();
    }

    void Compile::operator()(ast::InnerExp& e) {
        e.exp_get()->set_used(true);
        e.exp_get()->accept(*this);
    }

    void Compile::operator()(ast::NewExp& e) {
        auto array = std::dynamic_pointer_cast<ast::TypeArrayIdentifier>(e.alloc_get());
        if (array) {
            array->size_get()->set_used(e.is_used());
            array->size_get()->accept(*this);
        } else {
            auto dec = e.alloc_get()->type_name_get()->dec_get();
            auto type = std::dynamic_pointer_cast<ast::TypeStruct>(dec);
            assert(type);
            if (e.is_used())
                emitter_.emit<OP_PUSH, int64_t>(type->members_get().size());
        }
        if (e.is_used())
            emitter_.emit<OP_CREATE>();
    }

    void Compile::write(const char* filename) {
        std::ofstream file(filename);
        file << emitter_;
    }

    void Compile::save(tolk::TolkFile& t) {
        std::vector<char> end;
        for (auto& Ub : emitter_.buf_get()) {
            end.insert(end.end(), Ub.args_.begin(), Ub.args_.end());
        }
        t.set_bytecode(end);
        tolk::FuncTable f;
        for (auto e : dec_) {
            f.insert(e->number_get(),
                     tolk::Function(e->function_offset_get(), e->reg_size_get(), e->reg_offset_get())
                    );
        }
        t.set_functable(f);
    }
}
