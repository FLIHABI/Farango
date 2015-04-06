#ifndef TYPE_PROTOTYPE_HH
# define TYPE_PROTOTYPE_HH

# include <memory>

# include "type_identifier.hh"
# include "declaration.hh"
# include "visitor.hh"

namespace ast
{
    class TypePrototype : public Declaration
    {
        public:
            TypePrototype(std::shared_ptr<TypeIdentifier> type)
                : type_(type)
            {
                name_ = type->type_name_get();
            };

            virtual ~TypePrototype()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<TypeIdentifier> type_get()
            {
                return type_;
            }

        private:
            std::shared_ptr<TypeIdentifier> type_;

    };
}
# endif /* TYPE_PROTOTYPE_HH */
