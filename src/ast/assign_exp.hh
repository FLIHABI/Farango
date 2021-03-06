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
            AssignExp(std::shared_ptr<Value> lvalue, std::shared_ptr<Exp> exp)
                : lvalue_(lvalue)
                , exp_(exp)
            {}

            virtual ~AssignExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Value> lvalue_get()
            {
                return lvalue_;
            }
            std::shared_ptr<Exp> exp_get()
            {
                return exp_;
            }

#if 0
            virtual AssignExp* clone()
            {
                return new AssignExp(std::shared_ptr<Value>(lvalue_->clone()),
                                     std::shared_ptr<Exp>(exp_->clone()));
            }
#endif

        private:
            std::shared_ptr<Value> lvalue_;
            std::shared_ptr<Exp> exp_;

    };
}
#endif /* ASSIGN_EXP */
