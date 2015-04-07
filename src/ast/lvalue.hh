#ifndef LVALUE_HH
# define LVALUE_HH


#include "ast_all.hh"
#include "value.hh"
#include "visitor.hh"

namespace ast
{
    class Lvalue : public Value
    {
        public:
            Lvalue(Symbole s)
                : s_(s)
            {}
            virtual ~Lvalue()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            Symbole s_get()
            {
                return s_;
            }

        protected:
            Symbole s_;

    };
}

#endif /* LVALUE_HH */
