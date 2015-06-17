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

            inline std::weak_ptr<Declaration> type_value_get()
            {
                return type_value_;
            }

            inline void type_value_set(std::weak_ptr<Declaration> t)
            {
                type_value_ = t;
            }

            inline bool is_used()
            {
                return used_;
            }

            inline void set_used(bool used)
            {
                used_ = used;
            }

#if 0
            virtual Exp* clone() = 0;
#endif


        protected:
            std::weak_ptr<Declaration> type_value_;
            bool used_ = false;

    };
} // ast

#endif /* EXP_HH */
