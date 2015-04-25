#ifndef EXP_HH
# define EXP_HH

# include <memory>

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

            std::weak_ptr<Declaration> type_value_get()
            {
                return type_value_;
            }

            void type_value_set(std::weak_ptr<Declaration> t)
            {
                type_value_ = t;
            }

        protected:
            std::weak_ptr<Declaration> type_value_;

    };
} // ast

#endif /* EXP_HH */
