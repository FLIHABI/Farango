#ifndef EXP_HH
# define EXP_HH

# include "ast_all.hh"
# include "ast.hh"

namespace ast
{
    class Exp : public Ast
    {
        public:
            Exp()
            {};
            virtual ~Exp()
            {};

            void virtual accept(Visitor& v) = 0;
    };
} // ast

#endif /* EXP_HH */
