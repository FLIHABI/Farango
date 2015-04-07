
#ifndef DO_EXPR_HH
# define DO_EXPR_HH

# include <memory>

# include "visitor.hh"
# include "exp.hh"

namespace ast
{
    class DoExp : public Exp
    {
        public:
            DoExp(std::shared_ptr<Exp> condition, std::shared_ptr<Exp> body)
                : condition_(condition)
                , body_(body)
            {};

            virtual ~DoExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }


            std::shared_ptr<Exp> condition_get()
            {
                return condition_;
            }

            std::shared_ptr<Exp> body_get()
            {
                return body_;
            }

        private:
            std::shared_ptr<Exp> condition_;
            std::shared_ptr<Exp> body_;
    };
}

#endif /* DO_EXPR_HH */
