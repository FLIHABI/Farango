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
            TypePrototype(std::shared_ptr<TypeIdentifierDec> type)
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

            std::shared_ptr<TypeIdentifierDec> type_get()
            {
                return type_;
            }

            std::shared_ptr<TypePrototype> type_dec_get()
            {
                return type_dec_;
            }

            void type_dec_set(std::shared_ptr<TypePrototype> t)
            {
                type_dec_ = t;
            }

        protected:
            std::shared_ptr<TypeIdentifierDec> type_;
            std::shared_ptr<TypePrototype> type_dec_ = nullptr;
    };
}
# endif /* TYPE_PROTOTYPE_HH */
