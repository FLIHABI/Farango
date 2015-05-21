#ifndef COMPILER_HH_
# define COMPILER_HH_

# include "ast/default_visitor.hh"
# include "emitter.hh"
# include "commons/tolkfile/tolk-file.hh"

namespace compile {
    class Compile : public virtual ast::DefaultVisitor {
        using super = ast::DefaultVisitor;

    public:
        void write(const char* filename);
        void save(tolk::TolkFile&);

        void process(ast::Ast&);
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

        virtual void operator()(ast::FunCall& e) override;
        virtual void operator()(ast::FunctionDec& e) override;
        virtual void operator()(ast::IfExp& e) override;
        virtual void operator()(ast::MemberAccess& e) override;
        virtual void operator()(ast::ArrayAccess& e) override;
        virtual void operator()(ast::UnaryExp& e) override;
        virtual void operator()(ast::WhileExp& e) override;
        //TODO virtual void operator()(ast::String& e) override;
        virtual void operator()(ast::ExpListFunction& e) override;
        virtual void operator()(ast::VarAssign& e) override;
        //TODO virtual void operator()(ast::BreakExp& e) override;
        //TODO virtual void operator()(ast::ContinueExp& e) override;
        virtual void operator()(ast::NewExp& e) override;
        virtual void operator()(ast::InnerExp& e) override;

        std::vector<ast::FunctionDec*>& dec_get()
        {
            return dec_;
        }


    private:
        void assign_array(ast::ArrayAccess&, ast::AssignExp&);
        void assign_struct(ast::MemberAccess&, ast::AssignExp&);
        void assign_register(ast::Lvalue&, ast::AssignExp&);
        Emitter emitter_;
        std::vector<ast::FunctionDec*> dec_;
    };
}

#endif /* !COMPILER_HH_ */
