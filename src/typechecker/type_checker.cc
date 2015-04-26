# include "ast/all.hh"
# include "type_checker.hh"

namespace typechecker
{
    bool TypeChecker::is_equal(std::shared_ptr<ast::Declaration> a,
                               std::shared_ptr<ast::Declaration> b)
    {
        std::shared_ptr<ast::TypePrototype> a_ =
            std::dynamic_pointer_cast<ast::TypePrototype>(a);
        std::shared_ptr<ast::TypePrototype> b_ =
            std::dynamic_pointer_cast<ast::TypePrototype>(b);
        if (a_ && b_)
            return (a_->type_dec_get() && a_->type_dec_get() == b_->type_dec_get());
        return (a && a == b);
    }

    bool TypeChecker::is_int(std::shared_ptr<ast::Declaration> a)
    {
        return is_equal(a, ast::IntDec::get_def());
    }

    TypeChecker::TypeChecker(misc::error& e)
        : e_(e)
    {
    }

    TypeChecker::~TypeChecker()
    {
    }
    void TypeChecker::operator()(ast::Ast& a)
    {
        super::operator()(a);
    }

    void TypeChecker::operator()(ast::AssignExp& e)
    {
        super::operator()(e);
        e.type_value_set(e.lvalue_get()->type_value_get());
        if (!is_equal(e.lvalue_get()->type_value_get().lock(),
                    e.exp_get()->type_value_get().lock()))
        {
            //FIXME error
        }
    }

    void TypeChecker::operator()(ast::BinaryExp& e)
    {
        super::operator()(e);
        if (!is_int(e.valuel_get()->type_value_get().lock())
            || !is_int(e.valuel_get()->type_value_get().lock()))
        {
            //FIXME error
        }
        e.type_value_set(ast::IntDec::get_def());
    }

    void TypeChecker::operator()(ast::DoExp& e)
    {
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            //FIXME error
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpList& e)
    {
        super::operator()(e);
        //FIXME on empy list
        e.type_value_set(e.list_get()[0]->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpListInner& e)
    {
        super::operator()(e);
        //FIXME on empy list
        e.type_value_set(e.list_get()[0]->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpListFunction& e)
    {
        super::operator()(e);
        //FIXME on empy list
        e.type_value_set(e.list_get()[0]->type_value_get());
    }

    void TypeChecker::operator()(ast::ForExp& e)
    {
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            //FIXME error
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::FunCall& e)
    {
        super::operator()(e);
        std::shared_ptr<ast::Id> id =
            std::dynamic_pointer_cast<ast::Id>(e.value_get());
        if (!id)
        {
            //FIXME error
            //Something happen, we only support name () function call
        }
        std::shared_ptr<ast::FunctionDec> def =
            std::dynamic_pointer_cast<ast::FunctionDec>(id->dec_get());
        if (!def)
        {
            //FIXME error
            //id is not a function
        }

        if (e.list_get()->list_get().size() != def->params_get().size())
        {
            //FIXME error
            //
        }

        for (unsigned i = 0; i < def->params_get().size(); i++)
        {
            auto a = e.list_get()->list_get()[i]->type_value_get().lock();
            auto b = def->params_get()[i].type_get()->type_name_get()->dec_get();
            if (!is_equal(a, b)) // TypeChecker should have a pointer to they definition
            {
                //FIXME error
                // bad parameter
            }
        }

        if (def->return_t_get())
            e.type_value_set(def->return_t_get()->type_name_get()->dec_get());
        else
            e.type_value_set(ast::VoidDec::get_def());
    }

    void TypeChecker::operator()(ast::IfExp& e)
    {
        super::operator()(e);
        if (!is_int(e.if_get()->type_value_get().lock()))
        {
            //FIXME error
            //bad condition
        }
        if (!e.else_get()) //void
        {
            e.type_value_set(ast::VoidDec::get_def());
            return;
        }
        if (!is_equal(e.then_get()->type_value_get().lock(),
                      e.else_get()->type_value_get().lock()))
        {
            //FIXME error
            //Not the same return value
        }
        e.type_value_set(e.then_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::Lvalue& e)
    {
        super::operator()(e);
        e.type_value_set(e.s_get()->dec_get());
    }

    void TypeChecker::operator()(ast::FunctionPrototype& e)
    {
        auto def = e.type_dec_get();
        if (!def)
        {
            //FIXME error
            //Sould not happen
        }
        if (def->params_get().size() != e.params_get().size())
        {
            //FIXME error
        }

        for (unsigned i = 0; i < def->params_get().size(); i++)
        {
            auto a = e.params_get()[i].type_get()->type_name_get()->dec_get();
            auto b = def->params_get()[i].type_get()->type_name_get()->dec_get();
            if (!is_equal(a, b)) // TypeChecker should have a pointer to they definition
            {
                //FIXME error
                // bad parameter
            }
        }

        if (e.return_t_get() && !is_equal(e.return_t_get()->type_name_get()->dec_get(),
                                          def->return_t_get()->type_name_get()->dec_get()))
        {
                //FIXME error
        }
    }

    void TypeChecker::operator()(ast::FunctionDec& e)
    {
        super::operator()(e);
        if (e.return_t_get()
                && !is_equal(e.return_t_get()->type_name_get()->dec_get(),
                             e.body_get()->type_value_get().lock()))
        {
            //FIXME error
            //Not the same return value
        }
    }

    void TypeChecker::operator()(ast::MemberAccess& e)
    {
        super::operator()(e);
        auto l = e.lval_get()->type_value_get().lock();
        std::shared_ptr<ast::TypeStruct> t
            = std::dynamic_pointer_cast<ast::TypeStruct>(l);
        if (!t)
        {
            //FIXME error
            //not a struct
        }
        for (auto v : t->members_get())
        {
            if (v.name_get()->s_get() == e.s_get()->s_get())
            {
                e.type_value_set(v.type_get()->type_name_get()->dec_get());
                return;
            }
        }
        //FIXME error
        //No field
    }

    void TypeChecker::operator()(ast::UnaryExp& e)
    {
        super::operator()(e);
        e.type_value_set(ast::IntDec::get_def());
        if (!is_int(e.exp_get()->type_value_get().lock()))
        {
            //FIXME
            //error
        }
    }

    void TypeChecker::operator()(ast::WhileExp& e)
    {
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            //FIXME error
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::InnerExp& e)
    {
        super::operator()(e);
        e.type_value_set(e.exp_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::VarAssign& e)
    {
        super::operator()(e);
        if (!is_equal(e.value_get()->type_value_get().lock(),
                      e.type_get()->type_name_get()->dec_get()))
        {
            //FIXME error
        }
        e.type_value_set(e.value_get()->type_value_get());
    }
}
