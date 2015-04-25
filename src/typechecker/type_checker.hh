#ifndef TYPE_CHECKER_HH
# define TYPE_CHECKER_HH

# include "ast/default_visitor.hh"

namespace typechecker
{
    class TypeChecker : public virtual ast::DefaultVisitor
    {
            virtual void operator()(ast::AssignExp& e) override;
            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::BinaryExp& e) override;
            virtual void operator()(ast::Declaration& e) override;
            virtual void operator()(ast::DoExp& e) override;
            virtual void operator()(ast::Exp& e) override;
            virtual void operator()(ast::ExpList& e) override;
            virtual void operator()(ast::ForExp& e) override;
            virtual void operator()(ast::FunCall& e) override;

            virtual void operator()(ast::FunctionDec& e) override;
            virtual void operator()(ast::FunctionPrototype& e) override;

            virtual void operator()(ast::IfExp& e) override;
            virtual void operator()(ast::Int& e) override;
            virtual void operator()(ast::Literal& e) override;
            virtual void operator()(ast::Lvalue& e) override;
            virtual void operator()(ast::MemberAccess& e) override;
            virtual void operator()(ast::Number& e) override;
            virtual void operator()(ast::TypeIdentifierUse& e) override;
            virtual void operator()(ast::TypeIdentifierDec& e) override;
            virtual void operator()(ast::TypePrototype& e) override;
            virtual void operator()(ast::TypeStruct& e) override;
            virtual void operator()(ast::TypeUnion& e) override;
            virtual void operator()(ast::UnaryExp& e) override;
            virtual void operator()(ast::Value& e) override;
            virtual void operator()(ast::VarDec& e) override;
            virtual void operator()(ast::WhileExp& e) override;
            virtual void operator()(ast::String& e) override;
            virtual void operator()(ast::InnerExp& e) override;
            virtual void operator()(ast::ExpListInner& e) override;
            virtual void operator()(ast::ExpListFunction& e) override;
            virtual void operator()(ast::Id& e) override;
            virtual void operator()(ast::VarAssign& e) override;
    };
}

#endif /* TYPE_CHECKER_HH */
