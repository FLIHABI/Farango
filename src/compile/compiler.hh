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

    private:
        Emitter emitter_;
        binder::Binder binder_;
    };
}

#endif /* !COMPILER_HH_ */
