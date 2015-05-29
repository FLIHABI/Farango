#include "type_builder.hh"
#include "ast/pretty_print.hh"

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


    bool operator==(ast::TypeIdentifierDec& dec, ast::TypeIdentifierUse& use)
    {
        if (dec.specs_get().size() != use.specs_get().size())
            return false;
        for (unsigned i = 0; i < dec.specs_get().size(); i++)
        {
            if (dec.specs_get()[i]->name_get()->s_get() != use.specs_get()[i]->s_get())
                return false;
        }
        return true;
    }

    void build_struct(std::shared_ptr<ast::TypeStruct> source,
                      ast::TypeIdentifierUse& id,
                      std::map<misc::symbol, std::shared_ptr<ast::Id>>& map)
    {
        for (auto p : source->sub_type_get())
        {
            if (*p->type_get() == id)
            {
                id.type_name_get()->dec_change(p);
                return;
            }
        }

        auto new_struct = std::make_shared<ast::TypeStruct>(
                    std::make_shared<ast::TypeIdentifierDec>(source->type_get()->type_name_get())
                );

        for (auto& spec : id.specs_get())
            new_struct->type_get()->specs_get().push_back(std::make_shared<ast::Declaration>(spec));

        for (auto& field : source->members_get())
        {
            auto dec = field.type_get()->type_name_get()->dec_get();
            if (std::dynamic_pointer_cast<ast::TypeValue>(dec)) //Not a generic dec
                new_struct->members_get().push_back(field);
            else
            {
                if (map[field.type_get()->type_name_get()->s_get()])
                    new_struct->members_get().push_back(ast::VarDec(field.name_get(),
                                std::make_shared<ast::TypeIdentifierUse>(
                                    map[field.type_get()->type_name_get()->s_get()])
                                ));
                else
                {
                    //FIXME, error
                }
            }
        }

        source->sub_type_get().push_back(new_struct);
        id.type_name_get()->dec_change(new_struct);
        new_struct->type_dec_set(new_struct);
    }

    void TypeBuilder::operator()(ast::TypeIdentifierUse& e)
    {
        auto type = std::dynamic_pointer_cast<ast::TypePrototype>(e.type_name_get()->dec_get());
        if (e.specs_get().size() > 0 && type && type->type_get()->specs_get().size() == e.specs_get().size())
        {
            std::map<misc::symbol, std::shared_ptr<ast::Id>> mapping;
            for (unsigned i = 0; i < e.specs_get().size(); i++) {
                mapping[type->type_get()->specs_get()[i]->name_get()->s_get()] = e.specs_get()[i];
            }
            auto struct_ = std::dynamic_pointer_cast<ast::TypeStruct>(type);
            if (type)
                build_struct(struct_, e, mapping);
        }
        else if (type || e.specs_get().size() > 0) //FIXME ERROR
            std::cout << "Can't work on " << e<< std::endl;
    }
}
