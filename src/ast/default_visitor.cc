#include "default_visitor.hh"
#include "all.hh"

namespace ast
{
    DefaultVisitor::DefaultVisitor()
    {}

    DefaultVisitor::~DefaultVisitor()
    {}

    void DefaultVisitor::operator()(AssignExp& e)
    {
        e.lvalue_get()->accept(*this);
        e.exp_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Ast& a)
    {
        a.accept(*this);
    }

    void DefaultVisitor::operator()(BinaryExp& e)
    {
        e.valuel_get()->accept(*this);
        e.expr_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Declaration& e)
    {
    }

    void DefaultVisitor::operator()(DoExp& e)
    {
        e.condition_get()->accept(*this);
        e.body_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Exp& e)
    {
    }

    void DefaultVisitor::operator()(ExpList& e)
    {
        for (auto exp : e.list_get())
            exp->accept(*this);
    }

    void DefaultVisitor::operator()(ForExp& e)
    {
        e.init_get()->accept(*this);
        e.condition_get()->accept(*this);
        e.body_get()->accept(*this);
        e.end_get()->accept(*this);
    }

    void DefaultVisitor::operator()(FunCall& e)
    {
        e.value_get()->accept(*this);
        e.list_get()->accept(*this);
    }

    void DefaultVisitor::operator()(FunctionDec& e)
    {
        for (auto& var: e.params_get())
            var.accept(*this);
        e.body_get()->accept(*this);
    }

    void DefaultVisitor::operator()(FunctionPrototype& e)
    {
        for (auto& var: e.params_get())
            var.accept(*this);
    }

    void DefaultVisitor::operator()(IfExp& e)
    {
        e.if_get()->accept(*this);
        e.then_get()->accept(*this);
        if (e.else_get())
            e.else_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Int& e)
    {
    }

    void DefaultVisitor::operator()(Literal& e)
    {
    }

    void DefaultVisitor::operator()(Lvalue& e)
    {
    }

    void DefaultVisitor::operator()(MemberAccess& e)
    {
        e.lval_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Number& e)
    {
    }

    void DefaultVisitor::operator()(TypeIdentifier& e)
    {
    }

    void DefaultVisitor::operator()(TypePrototype& e)
    {
        e.type_get()->accept(*this);
    }

    void DefaultVisitor::operator()(TypeStruct& e)
    {
        e.type_get()->accept(*this);
        for (auto& var : e.members_get())
            var.accept(*this);
    }

    void DefaultVisitor::operator()(TypeUnion& e)
    {
        e.type_get()->accept(*this);
        for (auto& var : e.unions_get())
            var.accept(*this);
    }

    void DefaultVisitor::operator()(UnaryExp& e)
    {
        e.exp_get()->accept(*this);
    }

    void DefaultVisitor::operator()(Value& e)
    {
    }

    void DefaultVisitor::operator()(VarDec& e)
    {
        e.type_get()->accept(*this);
    }

    void DefaultVisitor::operator()(WhileExp& e)
    {
        e.condition_get()->accept(*this);
        e.body_get()->accept(*this);
    }

    void DefaultVisitor::operator()(String& e)
    {
    }

    void DefaultVisitor::operator()(InnerExp& e)
    {
        e.exp_get()->accept(*this);
    }
}
