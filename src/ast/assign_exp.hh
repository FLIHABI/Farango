#ifndef ASSIGN_EXP
# define ASSIGN_EXP

#include <memory>

#include "exp.hh"
#include "lvalue.hh"

namespace ast
{
    class AssignExp : public Exp
    {
        public:
            AssignExp(std::shared_ptr<Lvalue> lvalue, std::shared_ptr<Exp> exp)
                : lvalue_(lvalue)
                , exp_(exp)
            {}

            virtual ~AssignExp();

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            
            std::shared_ptr<Lvalue> lvalue_get()
            {
                return lvalue_;
            }
            std::shared_ptr<Exp> exp_get()
            {
                return exp_;
            }

        private:
            std::shared_ptr<Lvalue> lvalue_;
            std::shared_ptr<Exp> exp_;

    };
}
#endif /* ASSIGN_EXP */
