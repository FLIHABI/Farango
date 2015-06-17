#ifndef DO_EXPR_HH
# define DO_EXPR_HH

# include <memory>

# include "visitor.hh"
# include "exp.hh"
# include "loop_exp.hh"

namespace ast
{
    class DoExp : public LoopExp
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

#if 0
            virtual DoExp* clone()
            {
                return new DoExp(std::shared_ptr<Exp>(condition_->clone()),
                                 std::shared_ptr<Exp>(body_->clone()));
            }
#endif

        private:
            std::shared_ptr<Exp> condition_;
            std::shared_ptr<Exp> body_;
    };
}

#endif /* DO_EXPR_HH */
