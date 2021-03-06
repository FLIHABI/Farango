#ifndef TYPE_CHECKER_HH
# define TYPE_CHECKER_HH

# include <memory>
# include "ast/default_visitor.hh"
# include "lib/error.hh"

namespace typechecker
{
    class TypeChecker : public ast::DefaultVisitor
    {
        using super = ast::DefaultVisitor;

        public:
            TypeChecker(misc::error& e);
            ~TypeChecker();
            virtual void operator()(ast::AssignExp& e) override;
            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::BinaryExp& e) override;
            virtual void operator()(ast::DoExp& e) override;
            virtual void operator()(ast::ExpList& e) override;
            virtual void operator()(ast::ExpListInner& e) override;
            virtual void operator()(ast::ExpListFunction& e) override;
            virtual void operator()(ast::ForExp& e) override;
            virtual void operator()(ast::FunCall& e) override;

            virtual void operator()(ast::FunctionDec& e) override;
            virtual void operator()(ast::FunctionPrototype& e) override;

            virtual void operator()(ast::IfExp& e) override;
            virtual void operator()(ast::Lvalue& e) override;
            virtual void operator()(ast::MemberAccess& e) override;
            virtual void operator()(ast::UnaryExp& e) override;
            virtual void operator()(ast::WhileExp& e) override;
            virtual void operator()(ast::InnerExp& e) override;
            virtual void operator()(ast::VarAssign& e) override;
            virtual void operator()(ast::VarDec& e) override;
            virtual void operator()(ast::NewExp& e) override;
            virtual void operator()(ast::TypeArrayIdentifier& e) override;
            virtual void operator()(ast::ArrayAccess& e) override;

            /* FIXME check me for generic purpose
            virtual void operator()(ast::TypeIdentifierUse& e) override;
            virtual void operator()(ast::TypeIdentifierDec& e) override;
            virtual void operator()(ast::TypePrototype& e) override;
            virtual void operator()(ast::TypeUnion& e) override;
            */
            virtual void operator()(ast::TypeStruct& e) override;
            virtual void operator()(ast::OfferExp& e) override;
            virtual void operator()(ast::GetExp& e) override;
            virtual void operator()(ast::AskExp& e) override;

        private:
            bool equal(ast::Exp& e1, ast::Exp& e2);

            bool is_equal(std::shared_ptr<ast::Declaration> a,
                          std::shared_ptr<ast::Declaration> b);

            bool are_equal(std::set<std::weak_ptr<ast::Declaration>>& a,
                           std::set<std::weak_ptr<ast::Declaration>>& b);

            bool is_int(std::shared_ptr<ast::Declaration> a);
            misc::error& e_;
    };
}

#endif /* TYPE_CHECKER_HH */
