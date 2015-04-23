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
        super::operator()(e);
    }

    void Binder::operator()(ast::DoExp& e)
    {
        s_map_.start_scop();
        super::operator()(*e.body_get());
        s_map_.end_scop();

        s_map_.start_scop();
        super::operator()(*e.condition_get());
        s_map_.end_scop();
    }

    void Binder::operator()(ast::ForExp& e)
    {
        s_map_.start_scop();
        super::operator()(*e.init_get());
        super::operator()(*e.condition_get());
        super::operator()(*e.end_get());
        s_map_.start_scop();
        super::operator()(*e.body_get());
        s_map_.end_scop();
        s_map_.end_scop();
    }

    //CHECK FUNCTION PROTO111
    void Binder::operator()(ast::FunctionDec& e)
    {
        s_map_.push_dec(e);
        e.name_get()->accept(*this);
        s_map_.start_scop();
        for (auto& var: e.params_get())
            var.accept(*this);
        super::operator()(*e.body_get());
        s_map_.end_scop();
        if (e.return_t_get())
            e.return_t_get()->accept(*this);
    }

    void Binder::operator()(ast::FunctionPrototype& e)
    {
        s_map_.push_dec(e);

        s_map_.start_scop();
        for (auto& var: e.params_get())
            var.accept(*this);
        s_map_.end_scop();

        if (e.return_t_get())
            e.return_t_get()->accept(*this);
    }

    void Binder::operator()(ast::IfExp& e)
    {
        s_map_.start_scop();
        super::operator()(*e.if_get());

        s_map_.start_scop();
        super::operator()(*e.then_get());
        s_map_.end_scop();

        if (e.else_get())
        {
            s_map_.start_scop();
            super::operator()(*e.else_get());
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
        //FIXME Check the field later (TypeChecker)
        Binder::operator()(*e.s_get());
    }

    void Binder::operator()(ast::TypePrototype& e)
    {
        s_map_.push_dec(e);
    }

    void Binder::operator()(ast::TypeStruct& e)
    {
        s_map_.push_dec(e);
        e.name_get()->accept(*this);
        s_map_.start_scop();
        for (auto& aux : e.type_get()->specs_get())
        {
            s_map_.push_dec(*aux);
            aux->name_get()->accept(*this);
        }
        for (auto& var : e.members_get())
            var.accept(*this);
        s_map_.end_scop();
    }

    void Binder::operator()(ast::TypeUnion& e)
    {
        s_map_.push_dec(e);
        e.name_get()->accept(*this);
        s_map_.start_scop();
        for (auto& aux : e.type_get()->specs_get())
        {
            s_map_.push_dec(*aux);
            aux->name_get()->accept(*this);
        }
        for (auto& id : e.unions_get())
            id.accept(*this);
        s_map_.end_scop();
    }

    void Binder::operator()(ast::VarDec& e)
    {
        s_map_.push_dec(e);

        e.name_get()->accept(*this);
        e.type_get()->accept(*this);
    }

    void Binder::operator()(ast::VarAssign& e)
    {
        e.value_get()->accept(*this);

        s_map_.push_dec(e);

        e.name_get()->accept(*this);
        e.type_get()->accept(*this);
    }

    void Binder::operator()(ast::WhileExp& e)
    {
        s_map_.start_scop();
        super::operator()(*e.condition_get());
        super::operator()(*e.body_get());
        s_map_.end_scop();
    }

    void Binder::operator()(ast::ExpListInner& e)
    {
        s_map_.start_scop();
        super::operator()(e);
        s_map_.end_scop();
    }

    void Binder::operator()(ast::Id& e)
    {
        e.dec_set(s_map_.get_s_declaration(e.s_get()));
    }

}
