#ifndef LVALUE_HH
# define LVALUE_HH

# include <memory>
# include "ast_all.hh"
# include "value.hh"
# include "id.hh"
# include "visitor.hh"

namespace ast
{
    class Lvalue : public Value
    {
        public:
            Lvalue(std::shared_ptr<Id> s)
                : s_(s)
            {}

            Lvalue(misc::symbol s)
                : s_(std::make_shared<Id>(s))
            {}
            virtual ~Lvalue()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Id> s_get()
            {
                return s_;
            }

        protected:
            std::shared_ptr<Id> s_;

    };
}

#endif /* LVALUE_HH */
