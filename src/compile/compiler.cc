#include <fstream>
#include <iostream>
#include "ast/all.hh"
#include "compiler.hh"
#include <cassert>

namespace compile {

    static uint16_t reg_counter = 0;

    void Compile::operator()(ast::Ast& a) {
        super::operator()(a);
        emitter_.emit<OP_HALT>();
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
            case ast::PLUS:  emitter_.emit<OP_ADD>(); break;
            case ast::MINUS: emitter_.emit<OP_SUB>(); break;
            case ast::MUL:   emitter_.emit<OP_MUL>(); break;
            case ast::DIV:   emitter_.emit<OP_DIV>(); break;
            case ast::MOD:   emitter_.emit<OP_MOD>(); break;
            default: break;
        };
    }

    void Compile::operator()(ast::Lvalue &e) {
        super::operator()(e);
        std::shared_ptr<ast::Declaration> decl = e.s_get()->dec_get();

        if (std::shared_ptr<ast::VarDec> vardec = std::dynamic_pointer_cast<ast::VarDec>(decl)) {
            if (e.is_used())
                emitter_.emit<OP_PUSHR>(vardec->register_number_get());
            else
                return;
        } else {
            std::cerr << "Could not resolve symbol";
            // TODO: proper error handling, should not happend
        }
    }

    void Compile::operator()(ast::VarDec &e) {
        super ::operator()(e);
        e.register_number_set(reg_counter++);

        if (e.is_used()) //should never happend
            emitter_.emit<OP_PUSH>(0);
    }

    void Compile::operator()(ast::AssignExp &e) {
        e.exp_get()->set_used(true);
        super::operator()(*e.exp_get());

        std::shared_ptr<ast::Lvalue> lval = std::dynamic_pointer_cast<ast::Lvalue>(e.lvalue_get());
        if (!lval)
        {
            std::cerr << "Only support var assignement";
            // TODO: manage struct and array assignement
            return;
        }

        std::shared_ptr<ast::Declaration> decl = lval->s_get()->dec_get();

        if (std::shared_ptr<ast::VarDec> vardec = std::dynamic_pointer_cast<ast::VarDec>(decl)) {
            emitter_.emit<OP_POPR>(vardec->register_number_get());
            if (e.is_used()) //should never happend
                emitter_.emit<OP_PUSHR>(vardec->register_number_get());
        }

    }

    void Compile::operator()(ast::Int& e) {
        if (e.is_used())
            emitter_.emit<OP_PUSH>(e.value_get());
    }

    void Compile::operator()(ast::DoExp& e) {
        if (e.is_used())
            emitter_.emit<OP_PUSH>(0);
        long do_instruction = emitter_.get_current_length();
        if (e.is_used())
            emitter_.emit<OP_POP>();

        e.body_get()->set_used(e.is_used());
        e.body_get()->accept(*this);

        e.condition_get()->set_used(true);
        e.condition_get()->accept(*this);

        emitter_.emit<OP_PUSH>(0);
        emitter_.emit<OP_CMP>();
        emitter_.emit<OP_JNE>(0);

        long jmp_instruction = emitter_.get_current_length();

        //Set jump to the start of the do
        emitter_.buf_get()[emitter_.buf_get().size() - 1].args_[0] = do_instruction - jmp_instruction;
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

        long jmp_address = emitter_.emit<OP_JMP>(0);
        long jmp_instruction = emitter_.get_current_length();
        long body_instruction = emitter_.get_current_length();

        e.body_get()->set_used(e.is_used());
        e.body_get()->accept(*this);

        if (e.end_get())
            e.end_get()->accept(*this);

        long cond_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].args_[0] = cond_instruction - jmp_instruction;

        e.condition_get()->set_used(true);
        e.condition_get()->accept(*this);

        emitter_.emit<OP_PUSH>(0);
        emitter_.emit<OP_CMP>();
        emitter_.emit<OP_JNE>(0);

        cond_instruction = emitter_.get_current_length();

        emitter_.buf_get()[emitter_.buf_get().size() - 1].args_[0] = - (cond_instruction - body_instruction);

    }

    void Compile::operator()(ast::IfExp& e) {
        e.if_get()->set_used(true);
        e.if_get()->accept(*this);

        emitter_.emit<OP_PUSH>(0);
        emitter_.emit<OP_CMP>();

        long jmp_address = emitter_.emit<OP_JE>(0);
        long jmp_instruction = emitter_.get_current_length();

        e.then_get()->set_used(e.is_used());
        e.then_get()->accept(*this);

        long then_adress = emitter_.emit<OP_JMP>(0);
        long then_instruction = emitter_.get_current_length();
        emitter_.buf_get()[jmp_address].args_[0] = then_instruction - jmp_instruction;

        e.else_get()->set_used(e.is_used());
        e.else_get()->accept(*this);
        emitter_.buf_get()[then_adress].args_[0] = emitter_.get_current_length() - then_instruction;

    }

    void Compile::write(const char* filename) {
        std::ofstream file(filename);
        file << emitter_;
    }

}
