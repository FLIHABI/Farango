#ifndef WHILE_EXPR_HH
# define WHILE_EXPR_HH

# include <memory>

# include "visitor.hh"
# include "loop_exp.hh"
# include "exp.hh"

namespace ast
{
    class WhileExp : public LoopExp
    {
        public:
            WhileExp(std::shared_ptr<Exp> condition, std::shared_ptr<Exp> body)
                : condition_(condition)
                , body_(body)
            {};

            virtual ~WhileExp()
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

#endif /* WHILE_EXPR_HH */
