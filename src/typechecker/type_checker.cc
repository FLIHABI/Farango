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
}
