#ifndef AST_VISITOR_HXX
# define AST_VISITOR_HXX

# include "visitor.hh"

namespace ast {

    template <class E>
    void Visitor::operator()(E* e) {
        e->accept(*this);
    }

    template <typename E>
    void Visitor::accept(E* e) {
        if (e)
            e->accept(*this);
    }

}

#endif /* !AST_VISITOR_HXX */
