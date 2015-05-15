#ifndef NEW_EXP_HH
# define NEW_EXP_HH

# include <memory>

# include "visitor.hh"
# include "value.hh"

namespace ast
{
    class NewExp : public Value
    {
        public:
            NewExp(std::shared_ptr<TypeIdentifierUse>& alloc)
                : alloc_(alloc)
            {};

            virtual ~NewExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<TypeIdentifierUse>& alloc_get()
            {
                return alloc_;
            }
        private:
            std::shared_ptr<TypeIdentifierUse> alloc_;
    };
}

#endif /* NEW_EXP_HH */
