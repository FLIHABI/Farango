#ifndef UNARY_OP_HH
# define UNARY_OP_HH

# include <memory>

# include "exp.hh"
# include "operator.hh"
# include "visitor.hh"

namespace ast
{
    class UnaryExp : public Exp
    {
        public:
            UnaryExp(Operator op, std::shared_ptr<Exp> exp, misc::symbol opsym = "")
                : op_(op)
                , exp_(exp)
                , opsym_(opsym)
            {};

            virtual ~UnaryExp()
            {};

            Operator op_get()
            {
                return op_;
            }

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> exp_get()
            {
                return exp_;
            }

            misc::symbol& opsym_get()
            {
                return opsym_;
            }

        private:
            Operator op_;
            std::shared_ptr<Exp> exp_;
            misc::symbol opsym_;
    };
}

#endif /* UNARY_OP_HH */
