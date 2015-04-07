#ifndef BINARY_EXP_HH
# define BINARY_EXP_HH

# include <memory>

# include "ast_all.hh"
# include "visitor.hh"
# include "value.hh"
# include "operator.hh"

namespace ast
{
    class BinaryExp : public Value
    {
        public:
            BinaryExp(std::shared_ptr<Value> valuel, Operator op, std::shared_ptr<Exp> expr)
                : valuel_(valuel)
                , op_(op)
                , expr_(expr)
            {}

            virtual ~BinaryExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            
            std::shared_ptr<Value> valuel_get()
            {
                return valuel_;
            }

            Operator op_get()
            {
                return op_;
            }

            std::shared_ptr<Exp> expr_get()
            {
                return expr_;
            }

        private:
            std::shared_ptr<Value> valuel_;
            Operator op_;
            std::shared_ptr<Exp> expr_;
    };
}

#endif /* BINARY_EXP_HH */
