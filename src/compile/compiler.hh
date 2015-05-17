#ifndef COMPILER_HH_
# define COMPILER_HH_

# include "ast/default_visitor.hh"
# include "emitter.hh"
# include "binder/binder.hh"

namespace compile {
    class Compile : public virtual ast::DefaultVisitor {
        using super = ast::DefaultVisitor;

    public:
        void write(const char* filename);

        virtual void operator()(ast::AssignExp &e) override;
        virtual void operator()(ast::VarDec &e) override;
        virtual void operator()(ast::Ast& a) override;
        virtual void operator()(ast::BinaryExp& e) override;
        virtual void operator()(ast::Int& e) override;
        virtual void operator()(ast::Lvalue &e) override;
        virtual void operator()(ast::DoExp &e) override;
        virtual void operator()(ast::ExpList& e) override;
        virtual void operator()(ast::ExpListInner& e) override;
        virtual void operator()(ast::ForExp& e) override;

        //TODO virtual void operator()(ast::FunCall& e) override;
        //TODO virtual void operator()(ast::FunctionDec& e) override;
        virtual void operator()(ast::IfExp& e) override;
        //TODO virtual void operator()(MemberAccess& e) override;
        virtual void operator()(ast::UnaryExp& e) override;
        virtual void operator()(ast::WhileExp& e) override;
        //TODO virtual void operator()(ast::String& e) override;
        virtual void operator()(ast::ExpListFunction& e) override;
        virtual void operator()(ast::VarAssign& e) override;
    private:
        Emitter emitter_;
        unsigned current_flag = 1;
    };
}

#endif /* !COMPILER_HH_ */
