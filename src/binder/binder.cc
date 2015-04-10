#include "binder.hh"

#if 0
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
        s_map_.start_scop();
        s_map_.end_scop();
    }
}
#endif
