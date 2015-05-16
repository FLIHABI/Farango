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
        super::operator()(e);
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
            emitter_.emit<OP_PUSHR>(vardec->register_number_get());
        } else {
            std::cerr << "Could not resolve symbol";
            // TODO: proper error handling, should not happend
        }
    }

    void Compile::operator()(ast::VarDec &e) {
        super ::operator()(e);

        e.register_number_set(reg_counter++);
    }

    void Compile::operator()(ast::AssignExp &e) {
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
        }

    }

    void Compile::operator()(ast::Int& e) {
        emitter_.emit<OP_PUSH>(e.value_get());
    }

    void Compile::operator()(ast::DoExp& e) {
        emitter_.emit<OP_PUSH>(0);
        long do_instruction = emitter_.get_current_length();
        emitter_.emit<OP_POP>();

        e.body_get()->accept(*this);
        e.condition_get()->accept(*this);
        emitter_.emit<OP_PUSH>(0);
        emitter_.emit<OP_CMP>();
        emitter_.emit<OP_JNE>(0);
        long jmp_instruction = emitter_.get_current_length();

        //Set jump to the start of the do
        emitter_.buf_get()[emitter_.buf_get().size() - 1].args_[0] = - (jmp_instruction - do_instruction);
    }

    void Compile::write(const char* filename) {
        std::ofstream file(filename);
        file << emitter_;
    }

}
