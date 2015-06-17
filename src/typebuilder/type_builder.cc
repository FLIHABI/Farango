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
        auto& aux = dynamic_cast<ast::TypeIdentifierUse&>(e);
        operator()(aux);
        auto dec = e.type_name_get()->dec_get();
        std::shared_ptr<ast::TypeValue> t = std::dynamic_pointer_cast<ast::TypeValue>(dec);
        if (!t)
        {
            e_ << misc::error::error_type::type;
            e_ << dec << " is not a type" << std::endl;
            return;
        }
        e.set_dec(ast::ArrayBuilder::get().build(e.depth_get(), t));
    }

    bool operator==(ast::TypeIdentifierUse& t1, ast::TypeIdentifierUse& t2)
    {
        if (t1.type_name_get()->dec_get() != t2.type_name_get()->dec_get())
            return false;
        if (t1.specs_get().size() != t2.specs_get().size())
            return false;
        for (unsigned i = 0; i < t1.specs_get().size(); i++)
            if (!(*t1.specs_get()[i] == *t2.specs_get()[i]))
                    return false;
        return true;
    }

    bool operator==(ast::TypePrototype& dec, ast::TypeIdentifierUse& use)
    {
        if (dec.spec_kind_get().size() != use.specs_get().size())
            return false;
        for (unsigned i = 0; i < dec.spec_kind_get().size(); i++)
        {
            if (!(*dec.spec_kind_get()[i] == *use.specs_get()[i]))
                return false;
        }
        return true;
    }

    void TypeBuilder::build_struct(std::shared_ptr<ast::TypeStruct> source,
                      ast::TypeIdentifierUse& id,
                      std::map<misc::symbol, std::shared_ptr<ast::TypeIdentifierUse>>& map)
    {
        //Check for an existing definition
        for (auto p : source->sub_type_get())
        {
            if (*p == id)
            {
                id.type_name_get()->dec_change(p);
                return;
            }
        }

        std::shared_ptr<ast::TypeStruct> new_struct;
        //Building the new definition


        //FIXME
        if (std::dynamic_pointer_cast<ast::GetDec>(source))
            new_struct = std::make_shared<ast::GetDec>(
                    std::make_shared<ast::TypeIdentifierDec>(
                        std::make_shared<ast::Id>(*source->type_get()->type_name_get()))
                    );
        else
            new_struct = std::make_shared<ast::TypeStruct>(
                    std::make_shared<ast::TypeIdentifierDec>(
                        std::make_shared<ast::Id>(*source->type_get()->type_name_get()))
                    );

        for (auto& spec : id.specs_get())
            new_struct->type_get()->specs_get().emplace_back(std::make_shared<ast::Declaration>(
                        std::make_shared<ast::Id>(*spec->type_name_get())));

        for (auto& spec : id.specs_get())
            new_struct->spec_kind_get().push_back(spec);

        source->sub_type_get().push_back(new_struct);

        //FIXME: above this, could be factorised to be used in union type
        //Copying the fields
        for (auto& field : source->members_get())
        {
            auto dec = field.type_get()->type_name_get()->dec_get();
            if (std::dynamic_pointer_cast<ast::TypeValue>(dec)) //Not a generic dec
                new_struct->members_get().emplace_back(ast::VarDec(
                                std::make_shared<ast::Id>(*field.name_get()),
                                std::make_shared<ast::TypeIdentifierUse>(
                                    std::make_shared<ast::Id>(*field.type_get()->type_name_get()))
                            ));
            else
            {
                if (map[field.type_get()->type_name_get()->s_get()])
                {
                    new_struct->members_get().emplace_back(ast::VarDec(
                                std::make_shared<ast::Id>(*field.name_get()),
                                std::make_shared<ast::TypeIdentifierUse>(
                                    std::make_shared<ast::Id>(
                                        *map[field.type_get()->type_name_get()->s_get()]->type_name_get()))
                                ));
                }
                else
                {
                    //FIXME, error
                }
            }
            auto& new_field = new_struct->members_get()[new_struct->members_get().size() - 1] ;
            new_field.type_get()->specs_get().clear();
            for (auto& spec : field.type_get()->specs_get())
            {
                if (map[spec->type_name_get()->s_get()])
                    new_field.type_get()->specs_get().push_back(map[spec->type_name_get()->s_get()]);
                else
                    new_field.type_get()->specs_get().push_back(spec);
            }
        }

        //Finishing
        id.type_name_get()->dec_change(new_struct);
        new_struct->type_dec_set(new_struct);
        new_struct->accept(*this);
    }

    void TypeBuilder::operator()(ast::TypeIdentifierUse& e)
    {
        if (e.is_checked())
            return;
        e.set_checked(true);
        for (auto& spec : e.specs_get())
            spec->accept(*this);
        auto type = std::dynamic_pointer_cast<ast::TypePrototype>(e.type_name_get()->dec_get());
        if (e.specs_get().size() > 0 && type && type->type_get()->specs_get().size() == e.specs_get().size())
        {
            std::map<misc::symbol, std::shared_ptr<ast::TypeIdentifierUse>> mapping;
            for (unsigned i = 0; i < e.specs_get().size(); i++) {
                if (!std::dynamic_pointer_cast<ast::TypeValue>(e.specs_get()[i]->dec_get())) //Generic usage
                    return;
                mapping[type->type_get()->specs_get()[i]->name_get()->s_get()] = e.specs_get()[i];
            }
            auto struct_ = std::dynamic_pointer_cast<ast::TypeStruct>(type);
            if (struct_)
                build_struct(struct_, e, mapping);
        }
        else if (type || e.specs_get().size() > 0)
        {
            //FIXME: check the condition, maybe send an error
        }
    }

}
