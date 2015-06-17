#ifndef TYPE_ARRAY_HH
# define TYPE_ARRAY_HH

# include <memory>
# include <iostream>
# include <map>

# include "type_identifier.hh"
# include "declaration.hh"
# include "visitor.hh"
# include "type_value.hh"

namespace ast
{
    class TypeArray;
    class ArrayBuilder
    {

        public:
            std::shared_ptr<TypeArray> build(unsigned,
                                             std::shared_ptr<TypeValue>);

            static ArrayBuilder& get();

            const std::map<std::pair<unsigned, std::shared_ptr<TypeValue>>,
                     std::shared_ptr<TypeArray>>& map_get() const
            {
                return map_;
            }


        private:
            std::map<std::pair<unsigned, std::shared_ptr<TypeValue>>,
                     std::shared_ptr<TypeArray>> map_;
    };

    class TypeArray : public TypeValue
    {
        public:
            TypeArray(std::shared_ptr<TypeValue> type, unsigned depth)
                : type_(type)
                , depth_(depth)
            {
                if (depth_ > 1)
                    sub_type_ = ArrayBuilder::get().build(depth, type);
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

            virtual std::shared_ptr<TypeArray> sub_type_get()
            {
                return sub_type_;
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
