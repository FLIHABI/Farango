#include "binder.hh"

namespace binder
{
    Binder::Binder()
    {
    }

    Binder::~Binder()
    {
    }

    void Binder::operator()(ast::Ast& e)
    {
        DefaultVisitor::operator()(e);
    }

    void Binder::operator()(ast::DoExp& e)
    {
        s_map_.start_scop();
        DefaultVisitor::operator()(*e.body_get());
        s_map_.end_scop();

        s_map_.start_scop();
        DefaultVisitor::operator()(*e.body_get());
        s_map_.end_scop();
    }

    void Binder::operator()(ast::ForExp& e)
    {
        s_map_.start_scop();
        DefaultVisitor::operator()(*e.init_get());
        DefaultVisitor::operator()(*e.condition_get());
        DefaultVisitor::operator()(*e.end_get());
        s_map_.start_scop();
        DefaultVisitor::operator()(*e.body_get());
        s_map_.end_scop();
        s_map_.end_scop();
    }

    //CHECK FUNCTION PROTO111
    void Binder::operator()(ast::FunctionDec& e)
    {
        s_map_.push_dec(e);
        s_map_.start_scop();
        for (auto& var: e.params_get())
            var.accept(*this);
        DefaultVisitor::operator()(*e.body_get());
        s_map_.end_scop();
    }

    void Binder::operator()(ast::FunctionPrototype& e)
    {
        s_map_.push_dec(e);
    }

    void Binder::operator()(ast::IfExp& e)
    {
        s_map_.start_scop();
        DefaultVisitor::operator()(*e.if_get());

        s_map_.start_scop();
        DefaultVisitor::operator()(*e.then_get());
        s_map_.end_scop();

        if (e.else_get())
        {
            s_map_.start_scop();
            DefaultVisitor::operator()(*e.else_get());
            s_map_.end_scop();
        }

        s_map_.end_scop();
    }

    void Binder::operator()(ast::Lvalue& e)
    {
        Binder::operator()(*e.s_get());
    }

    void Binder::operator()(ast::MemberAccess& e)
    {
        //FIXME Check the field later
        Binder::operator()(*e.s_get());
    }
}
