#include "ast/all.hh"
#include "compiler.hh"

namespace compile {

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

    void Compile::operator()(ast::Int& e) {
        emitter_.emit<OP_PUSH, uint64_t>(e.get_value());
    }

}
