#include "register.hh"

namespace compile {
    FunctionRegister::FunctionRegister(std::vector<ast::FunctionDec*>& dec)
        : dec_(dec)
    {
    }

    void FunctionRegister::operator()(ast::Ast& a)
    {
        super::operator()(a);
    }

    void FunctionRegister::operator()(ast::FunctionDec& e)
    {
        dec_.push_back(&e);
        super::operator()(e);
    }

    /* --- */

    Register::Register(std::vector<ast::FunctionDec*>& dec,
                       std::vector<ast::TypeStruct*>& struct_table,
                       std::vector<ast::TypeUnion*>& union_table)
        : dec_(dec)
        , struct_table_(struct_table)
        , union_table_(union_table)
    {
    }

    void Register::operator()(ast::Ast& a)
    {
        super::operator()(a);
    }

    void Register::operator()(ast::FunctionDec& e)
    {
        //There is nothing here, Everything ok
    }

    void Register::operator()(ast::TypeStruct& e)
    {
        e.number_set(type_id_++);
        struct_table_.push_back(&e);
        for (auto& sub : e.sub_type_get())
            sub->accept(*this);
    }

    void Register::operator()(ast::TypeUnion& e)
    {
        e.number_set(type_id_++);
        union_table_.push_back(&e);
        for (auto& sub : e.sub_type_get())
            sub->accept(*this);
    }

    void Register::operator()(ast::TypeArray& e)
    {
        std::cout << "Just find a type array" << std::endl;
    }

    void Register::operator()(ast::VarDec& e)
    {
        e.number_set(register_id_++);
    }

    void Register::operator()(ast::VarAssign& e)
    {
        e.number_set(register_id_++);
        e.value_get()->accept(*this);
    }

    void Register::process(ast::Ast& a)
    {
        FunctionRegister fr(dec_);
        fr(a);

        operator()(a);

        for (auto& f : dec_)
        {
            uint16_t start = register_id_;
            f->number_set(function_id_++);
            for (auto& v : f->params_get())
                v.accept(*this);
            f->body_get()->accept(*this);
            uint16_t end = register_id_;
            f->reg_offset_set(start);
            f->reg_size_set(end - start);
        }

        for (auto& p : ast::ArrayBuilder::get().map_get())
        {
            p.second->number_set(type_id_++);
        }
    }
}
