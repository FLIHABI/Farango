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
            BinaryExp(std::shared_ptr<Exp> valuel, Operator op, std::shared_ptr<Exp> expr, misc::symbol opsym = "")
                : valuel_(valuel)
                , op_(op)
                , expr_(expr)
                , opsym_(opsym)
            {}

            virtual ~BinaryExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> valuel_get()
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

            misc::symbol& opsym_get()
            {
                return opsym_;
            }

#if 0
            virtual BinaryExp* clone()
            {
                return new BinaryExp(std::shared_ptr<Exp>(valuel_->clone()),
                                     op_,
                                     std::shared_ptr<Exp>(expr_->clone()),
                                     opsym_);
            }
#endif

        private:
            std::shared_ptr<Exp> valuel_;
            Operator op_;
            std::shared_ptr<Exp> expr_;
            misc::symbol opsym_;
    };
}

#endif /* BINARY_EXP_HH */
