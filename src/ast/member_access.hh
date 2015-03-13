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
            MemberAccess(std::shared_ptr<Lvalue> lval, Symbole s)
                : Lvalue(s)
                , lval_(lval)
            {}

            ~MemberAccess();

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Lvalue> lval_get()
            {
                return lval_;
            }

        private:
            std::shared_ptr<Lvalue> lval_;

    };
}

#endif /* MEMBER_ACCESS_HH */