#ifndef TYPE_ARRAY_HH
# define TYPE_ARRAY_HH

# include <memory>
# include <iostream>

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
            {
                if (depth_ > 1)
                    sub_type_ = std::make_shared<TypeArray>(type, depth_ - 1);
            }

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
                return sub_type_;
            }

        private:
            std::shared_ptr<TypeValue> type_;
            std::shared_ptr<TypeArray> sub_type_ = nullptr;
            unsigned depth_;
    };
}

#endif /* TYPE_ARRAY_HH */
