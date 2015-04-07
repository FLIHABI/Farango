#ifndef IF_EXP_HH
# define IF_EXP_HH

# include <memory>

# include "visitor.hh"
# include "exp.hh"
namespace ast
{
    class IfExp : public Exp
    {
        public:
            IfExp(std::shared_ptr<Exp> if_exp, std::shared_ptr<Exp> then_exp, 
                  std::shared_ptr<Exp> else_exp)
                : if_(if_exp)
                , then_(then_exp)
                , else_(else_exp)
            {};

            virtual ~IfExp()
            {};


            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> if_get()
            {
                return if_;
            }
            std::shared_ptr<Exp> then_get()
            {
                return then_;
            };
            std::shared_ptr<Exp> else_get()
            {
                return else_;
            }

        private:
            std::shared_ptr<Exp> if_;
            std::shared_ptr<Exp> then_;
            std::shared_ptr<Exp> else_;
    };
}

#endif /* IF_EXP_HH */
