#ifndef AST_HH
# define AST_HH

#include "ast_all.hh"

namespace ast
{
    class Ast
    {
        public:
            Ast()
            {}
            virtual ~Ast()
            {}

            void virtual accept(Visitor& v) = 0;
    };
} // ast

#endif /* AST_HH */
