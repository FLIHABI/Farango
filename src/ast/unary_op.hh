#ifndef UNARY_OP_HH
# define UNARY_OP_HH

# include <memory>

# include "exp.hh"
# include "operator.hh"
# include "visitor.hh"

namespace ast
{
    class UnaryExp : Exp
    {
        public:
            UnaryExp(Operator op, std::shared_ptr<Exp> exp)
                : op_(op)
                , exp_(exp)
            {};

            ~UnaryExp();

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

        private:
            Operator op_;
            std::shared_ptr<Exp> exp_;
    };
}

#endif /* UNARY_OP_HH */
