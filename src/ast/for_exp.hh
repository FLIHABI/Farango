#ifndef FOR_EXP_HH
# define FOR_EXP_HH

# include <memory>

# include "visitor.hh"
# include "exp.hh"
# include "loop_exp.hh"

namespace ast
{
    class ForExp : public LoopExp
    {
        public:
            ForExp(std::shared_ptr<Exp> init, std::shared_ptr<Exp> condition,
                   std::shared_ptr<Exp> end, std::shared_ptr<Exp> body)
                : init_(init)
                , condition_(condition)
                , end_(end)
                , body_(body)
            {};

            virtual ~ForExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> init_get()
            {
                return init_;
            }

            std::shared_ptr<Exp> condition_get()
            {
                return condition_;
            }

            std::shared_ptr<Exp> end_get()
            {
                return end_;
            }

            std::shared_ptr<Exp> body_get()
            {
                return body_;
            }

        private:
            std::shared_ptr<Exp> init_;
            std::shared_ptr<Exp> condition_;
            std::shared_ptr<Exp> end_;
            std::shared_ptr<Exp> body_;
    };
}

#endif /* FOR_EXP_HH */
