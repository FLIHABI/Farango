#include "type_array.hh"

namespace ast
{
    std::shared_ptr<TypeArray>
    ArrayBuilder::build(unsigned depth, std::shared_ptr<TypeValue> value)
    {
        auto p = std::make_pair(depth, value);
        auto it = map_.find(p);
        if (it != map_.end())
            return it->second;
        auto ptr = std::make_shared<TypeArray>(value, depth);
        map_[std::move(p)] = ptr;
        return ptr;
    }

    ArrayBuilder& ArrayBuilder::get()
    {
        static ArrayBuilder arr;
        return arr;
    }
}
