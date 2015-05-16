#include "type_builder.hh"

namespace typebuilder
{
    TypeBuilder::TypeBuilder(misc::error& e)
        : e_(e)
    {}

    TypeBuilder::~TypeBuilder()
    {}

    void TypeBuilder::operator()(ast::Ast& a)
    {
        super::operator()(a);
    }

    void TypeBuilder::operator()(ast::TypeArrayIdentifier& e)
    {
        auto dec = e.type_name_get()->dec_get();
        std::shared_ptr<ast::TypeValue> t = std::dynamic_pointer_cast<ast::TypeValue>(dec);
        if (!t)
        {
            e_ << misc::error::error_type::type;
            e_ << dec << " is not a type" << std::endl;
            return;
        }
        e.set_dec(std::make_shared<ast::TypeArray>(t, e.depth_get()));
    }
}
