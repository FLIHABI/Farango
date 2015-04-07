#ifndef INNER_EXP_HH
# define INNER_EXP_HH

#include <memory>

#include "value.hh"
#include "visitor.hh"

namespace ast
{
    class InnerExp : public Value
    {
        public:
            InnerExp(std::shared_ptr<Exp> exp)
                : exp_(exp)
            {}

            virtual ~InnerExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> exp_get()
            {
                return exp_;
            }
        private:
            std::shared_ptr<Exp> exp_;
    };
}

#endif /* INNER_EXP_HH */
