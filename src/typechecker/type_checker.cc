# include <iostream>

# include "ast/pretty_print.hh"
# include "ast/all.hh"
# include "type_checker.hh"

namespace typechecker
{
    //TODO expression printing

    bool operator==(ast::TypeArray& a, ast::TypeArray& b)
    {
        if (a.type_get() != b.type_get())
            return false;
        return a.depth_get() == b.depth_get();
    }

    //Hack, FIXME later
    void sanitize(ast::Exp& e)
    {
        if (!e.type_value_get().lock())
            e.type_value_set(ast::NullDec::get_def());
    }

    bool TypeChecker::is_equal(std::shared_ptr<ast::Declaration> a,
                               std::shared_ptr<ast::Declaration> b)
    {
        {
            auto a_ = std::dynamic_pointer_cast<ast::TypePrototype>(a);
            auto b_ = std::dynamic_pointer_cast<ast::TypePrototype>(b);
            if (a_ && b_)
                return (a_->type_dec_get() && a_->type_dec_get() == b_->type_dec_get());
        }
        {
            auto a_ = std::dynamic_pointer_cast<ast::TypeArray>(a);
            auto b_ = std::dynamic_pointer_cast<ast::TypeArray>(b);
            if (a_ && b_)
                return (*a_ == *b_);
        }
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
        sanitize(e);
        super::operator()(e);
        e.type_value_set(e.lvalue_get()->type_value_get());

        if (!is_equal(e.lvalue_get()->type_value_get().lock(),
                    e.exp_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << e.lvalue_get()
                << " is of type " << e.lvalue_get()->type_value_get().lock()
                << " but is assigned with a "
                << e.exp_get()->type_value_get().lock()
                << std::endl;
        }
    }

    void TypeChecker::operator()(ast::BinaryExp& e)
    {
        sanitize(e);
        super::operator()(e);
        if (e.op_get() >= ast::Operator::GREATER && e.op_get() <= ast::Operator::LESS_EQ) {
            if (!is_equal(e.valuel_get()->type_value_get().lock(),
                          e.expr_get()->type_value_get().lock()))
            {
                e_ << misc::error::error_type::type;
                e_ << "component of " << &e << " are not of the same type" << std::endl;
            }
        }
        else if (!is_int(e.valuel_get()->type_value_get().lock())
            || !is_int(e.expr_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "one of the component of " << &e
               << " is not an int"
                << std::endl;
        }
        e.type_value_set(ast::IntDec::get_def());
    }

    void TypeChecker::operator()(ast::DoExp& e)
    {
        sanitize(e);
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "the condition " << e.condition_get()
               << " is not an int "
               << std::endl;
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpList& e)
    {
        sanitize(e);
        super::operator()(e);
        if (e.list_get().size() == 0)
            e.type_value_set(ast::VoidDec::get_def());
        else
            e.type_value_set(e.list_get()[e.list_get().size() - 1]->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpListInner& e)
    {
        sanitize(e);
        super::operator()(e);
        if (e.list_get().size() == 0)
            e.type_value_set(ast::VoidDec::get_def());
        else
            e.type_value_set(e.list_get()[e.list_get().size() - 1]->type_value_get());
    }

    void TypeChecker::operator()(ast::ExpListFunction& e)
    {
        sanitize(e);
        super::operator()(e);
        if (e.list_get().size() == 0)
            e.type_value_set(ast::VoidDec::get_def());
        else
            e.type_value_set(e.list_get()[e.list_get().size() - 1]->type_value_get());
    }

    void TypeChecker::operator()(ast::ForExp& e)
    {
        sanitize(e);
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "the condition " << e.condition_get()
               << " is not an int "
               << std::endl;
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::FunCall& e)
    {
        sanitize(e);
        super::operator()(e);
        std::shared_ptr<ast::Lvalue> id =
            std::dynamic_pointer_cast<ast::Lvalue>(e.value_get());
        if (!id)
        {
            e_ << misc::error::error_type::type;
            e_ << e.value_get()
               << " is not callable"
               << std::endl;
            return;
        }
        std::shared_ptr<ast::FunctionPrototype> def_ =
            std::dynamic_pointer_cast<ast::FunctionPrototype>(id->s_get()->dec_get());
        if (!def_)
        {
            e_ << misc::error::error_type::type;
            e_ << e.value_get()
               << " is not callable"
               << std::endl;
            return;
        }
        std::shared_ptr<ast::FunctionDec> def = std::dynamic_pointer_cast<ast::FunctionDec>(def_->type_dec_get());
        if (!def)
        {
            e_ << misc::error::error_type::type;
            e_ << e.value_get()
               << " is not callable"
               << std::endl;
            return;
        }

        e.func_set(def);

        if (e.list_get()->list_get().size() != def->params_get().size())
        {
            e_ << misc::error::error_type::type;
            e_ << def << " has " << def->params_get().size()
               << " only " << e.list_get()->list_get().size()
               << " were provided" << std::endl;
            return;
        }

        for (unsigned i = 0; i < def->params_get().size(); i++)
        {
            auto a = e.list_get()->list_get()[i]->type_value_get().lock();
            auto b = def->params_get()[i].type_get()->dec_get();
            if (!is_equal(a, b)) // TypeChecker should have a pointer to they definition
            {
                e_ << misc::error::error_type::type;
                e_ << a << " does not match with " << b;
            }
        }

        if (def->return_t_get())
            e.type_value_set(def->return_t_get()->dec_get());
        else
            e.type_value_set(ast::VoidDec::get_def());
    }

    void TypeChecker::operator()(ast::IfExp& e)
    {
        sanitize(e);
        super::operator()(e);
        if (!is_int(e.if_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "the condition " << e.if_get()
               << " is not an int "
               << std::endl;
        }
        if (!e.else_get()) //void
        {
            e.type_value_set(ast::VoidDec::get_def());
            return;
        }
        if (!is_equal(e.then_get()->type_value_get().lock(),
                      e.else_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << e.then_get()
               << " and "
               << e.else_get()
               << " has not the same type"
               << std::endl;
        }
        e.type_value_set(e.then_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::Lvalue& e)
    {
        sanitize(e);
        super::operator()(e);
        auto var = std::dynamic_pointer_cast<ast::VarDec>(e.s_get()->dec_get());
        if (var)
            e.type_value_set(var->type_get()->dec_get());
        else if (std::dynamic_pointer_cast<ast::FunctionPrototype>(e.s_get()->dec_get()))
            e.type_value_set(e.s_get()->dec_get());
    }

    void TypeChecker::operator()(ast::FunctionPrototype& e)
    {
        sanitize(e);
        auto def = e.type_dec_get();
        if (!def)
        {
            //FIXME error
            //Sould not happen
        }
        if (def->params_get().size() != e.params_get().size())
        {
            e_ << misc::error::error_type::type;
            e_ << " prototype " << &e
               << " does not match with it definition "
               << def;
            return;
        }

        for (unsigned i = 0; i < def->params_get().size(); i++)
        {
            auto a = e.params_get()[i].type_get()->dec_get();
            auto b = def->params_get()[i].type_get()->dec_get();
            if (!is_equal(a, b)) // TypeChecker should have a pointer to they definition
            {
                e_ << misc::error::error_type::type;
                e_ << " prototype " << &e
                    << " does not match with it definition "
                    << def;
                return;
            }
        }

        if (e.return_t_get() && !is_equal(e.return_t_get()->dec_get(),
                                          def->return_t_get()->dec_get()))
        {
            e_ << misc::error::error_type::type;
            e_ << " prototype " << &e
                << " does not match with it definition "
                << def;
            return;
        }
    }

    void TypeChecker::operator()(ast::FunctionDec& e)
    {
        sanitize(e);
        super::operator()(e);

        if (auto ati = std::dynamic_pointer_cast<ast::AutoTypeIdentifier>(e.return_t_get()))
            ati->type_set(e.body_get()->type_value_get());

        if (e.return_t_get()
                && !is_equal(e.return_t_get()->dec_get(),
                             e.body_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << " return type of " << e.return_t_get()
                << " does not match with " << &e << std::endl;
        }
    }

    void TypeChecker::operator()(ast::MemberAccess& e)
    {
        sanitize(e);
        super::operator()(e);
        auto l = e.lval_get()->type_value_get().lock();
        std::shared_ptr<ast::TypePrototype> t_
            = std::dynamic_pointer_cast<ast::TypePrototype>(l);
        if (!t_)
        {
            e_ << misc::error::error_type::type;
            e_ << e.lval_get()
                << " is not a TypePrototype" << std::endl;
            return;
        }

        std::shared_ptr<ast::TypeStruct> t
            = std::dynamic_pointer_cast<ast::TypeStruct>(t_->type_dec_get());

        if (!t)
        {
            e_ << misc::error::error_type::type;
            e_ << e.lval_get()
                << " is not a TypeStruct" << std::endl;
            return;
        }

        e.def_set(t);

        for (auto& v : t->members_get())
        {
            if (v.name_get()->s_get() == e.s_get()->s_get())
            {
                //FIXME, not sexy
                e.s_get()->dec_set(std::shared_ptr<ast::VarDec>(&v, [](void *){}));
                e.type_value_set(v.type_get()->dec_get());
                return;
            }
        }
        e_ << misc::error::error_type::type;
        e_ << e.lval_get()->type_value_get().lock()
            << " has no field " << e.s_get() << std::endl;
    }

    void TypeChecker::operator()(ast::UnaryExp& e)
    {
        sanitize(e);
        super::operator()(e);
        e.type_value_set(ast::IntDec::get_def());
        if (!is_int(e.exp_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << e.exp_get() << " is not an int" << std::endl;
        }
    }

    void TypeChecker::operator()(ast::WhileExp& e)
    {
        sanitize(e);
        super::operator()(e);
        if (!is_int(e.condition_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "the condition " << e.condition_get()
               << " is not an int "
               << std::endl;
        }
        e.type_value_set(e.body_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::InnerExp& e)
    {
        sanitize(e);
        super::operator()(e);
        e.type_value_set(e.exp_get()->type_value_get());
    }

    void TypeChecker::operator()(ast::VarAssign& e)
    {
        sanitize(e);
        super::operator()(e);

        if (auto ati = std::dynamic_pointer_cast<ast::AutoTypeIdentifier>(e.vardec_get()->type_get()))
            ati->type_set(e.value_get()->type_value_get());

        auto t = e.type_get()->dec_get();
        if (!std::dynamic_pointer_cast<ast::TypeValue>(t))
        {
            e_ << misc::error::error_type::type;
            e_ << "bad var type" << std::endl;
            return;
        }

        if (!is_equal(e.value_get()->type_value_get().lock(),
                      e.type_get()->dec_get()))
        {
            e_ << misc::error::error_type::type;
            e_ << e.value_get()
                << " is of type " << e.value_get()->type_value_get().lock()
                << " but is assigned with a "
                << e.type_get()->dec_get()
                << std::endl;
        }
        e.type_value_set(e.value_get()->type_value_get());
    }
    void TypeChecker::operator()(ast::VarDec& e)
    {
        sanitize(e);
        super::operator()(e);
        auto t = e.type_get()->dec_get();
        if (!std::dynamic_pointer_cast<ast::TypeValue>(t))
        {
            e_ << misc::error::error_type::type;
            e_ << "bad var type" << std::endl;
            return;
        }
    }

    void TypeChecker::operator()(ast::NewExp& e)
    {
        sanitize(e);
        super::operator()(e);
        auto a = std::dynamic_pointer_cast<ast::TypeArray>(e.alloc_get()->dec_get());
        auto b = std::dynamic_pointer_cast<ast::TypePrototype>(e.alloc_get()->dec_get());
        if (!a && !b)
        {
            e_ << misc::error::error_type::type;
            e_ << "new does not support this type" << std::endl;
            return;
        }
        e.type_value_set(e.alloc_get()->dec_get());
    }

    void TypeChecker::operator()(ast::TypeArrayIdentifier& e)
    {
        sanitize(e);
        super::operator()(e);
        if (!e.size_get())
            return;
        if (!is_int(e.size_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << "Could not create an array with" << e.size_get() << std::endl;
        }
    }

    void TypeChecker::operator()(ast::ArrayAccess& e)
    {
        sanitize(e);
        super::operator()(e);
        auto l = std::dynamic_pointer_cast<ast::TypeArray>(e.val_get()->type_value_get().lock());
        if (!is_int(e.offset_get()->type_value_get().lock()))
        {
            e_ << misc::error::error_type::type;
            e_ << e.offset_get() << " is not an int" << std::endl;
        }
        if (!l)
        {
            e_ << misc::error::error_type::type;
            e_ << e.val_get() << " is not an array" << std::endl;
            return;
        }
        e.type_value_set(l->access_type());
    }
}
