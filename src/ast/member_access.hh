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
            MemberAccess(std::shared_ptr<Value> lval, Symbole s)
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

        private:
            std::shared_ptr<Value> lval_;

    };
}

#endif /* MEMBER_ACCESS_HH */
