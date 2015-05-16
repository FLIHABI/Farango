#ifndef TYPE_ARRAY_HH
# define TYPE_ARRAY_HH

# include <memory>

# include "type_identifier.hh"
# include "declaration.hh"
# include "visitor.hh"
# include "type_value.hh"

namespace ast
{
    class TypeArray : public TypeValue
    {
        public:
            TypeArray(std::shared_ptr<TypeValue> type, unsigned depth)
                : type_(type)
                , depth_(depth)
            {}

            virtual ~TypeArray()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            unsigned depth_get()
            {
                return depth_;
            }

            virtual std::shared_ptr<TypeValue> type_get()
            {
                return type_;
            }

            std::shared_ptr<TypeValue> access_type()
            {
                if (depth_ == 1)
                    return type_;
                return std::make_shared<TypeArray>(type_, depth_ - 1);
            }

        private:
            std::shared_ptr<TypeValue> type_;
            unsigned depth_;
    };
}

#endif /* TYPE_ARRAY_HH */
