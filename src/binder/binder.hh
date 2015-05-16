#ifndef BINDER_HH
# define BINDER_HH

# include "scoped_map.hh"
# include "ast/default_visitor.hh"
# include "lib/error.hh"

namespace binder
{
    class Binder : public ast::DefaultVisitor
    {
        using super = ast::DefaultVisitor;

        public:
            Binder(misc::error& e);
            ~Binder();

            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::DoExp& e) override;
            virtual void operator()(ast::ForExp& e) override;

            virtual void operator()(ast::FunctionDec& e) override;
            virtual void operator()(ast::FunctionPrototype& e) override;

            virtual void operator()(ast::IfExp& e) override;

            virtual void operator()(ast::Lvalue& e) override;
            virtual void operator()(ast::MemberAccess& e) override;

            virtual void operator()(ast::TypePrototype& e) override;
            virtual void operator()(ast::TypeStruct& e) override;
            virtual void operator()(ast::TypeUnion& e) override;

            virtual void operator()(ast::VarDec& e) override;
            virtual void operator()(ast::VarAssign& e) override;
            virtual void operator()(ast::WhileExp& e) override;

            virtual void operator()(ast::ExpListInner& e) override;
            virtual void operator()(ast::ExpList& e) override;
            virtual void operator()(ast::Id& e) override;

            virtual void operator()(ast::BreakExp& e) override;
            virtual void operator()(ast::ContinueExp& e) override;

        private:
            ScopedMap s_map_;
            misc::error& e_;
            std::shared_ptr<ast::LoopExp> current_loop = nullptr;
    };
}
#endif /* BINDER_HH */
