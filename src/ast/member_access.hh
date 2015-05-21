#ifndef MEMBER_ACCESS_HH
# define MEMBER_ACCESS_HH

# include <memory>

# include "lvalue.hh"
# include "visitor.hh"

namespace ast
{
    class MemberAccess : public Lvalue
    {
        public:
            MemberAccess(std::shared_ptr<Value> lval, std::shared_ptr<Id> s)
                : Lvalue(s)
                , lval_(lval)
            {};

            virtual ~MemberAccess()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Value> lval_get()
            {
                return lval_;
            }

            std::shared_ptr<TypeStruct> def_get()
            {
                return def_;
            }

            void def_set(std::shared_ptr<TypeStruct> def)
            {
                def_ = def;
            }

        private:
            std::shared_ptr<Value> lval_;
            std::shared_ptr<TypeStruct> def_;

    };
}

#endif /* MEMBER_ACCESS_HH */
