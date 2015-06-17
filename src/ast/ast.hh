#ifndef AST_HH
# define AST_HH

# include <memory>

# include "ast_all.hh"

namespace ast
{
    class Ast
    {
        public:
            Ast()
            {}
            virtual ~Ast()
            {}

#if 0
            virtual Ast* clone() = 0;
#endif

            void virtual accept(Visitor& v) = 0;
    };
} // ast

#endif /* AST_HH */
