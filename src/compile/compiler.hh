#ifndef COMPILER_HH_
# define COMPILER_HH_

# include "ast/default_visitor.hh"
# include "emitter.hh"

namespace compile {
    class Compile : public virtual ast::DefaultVisitor {
        using super = ast::DefaultVisitor;

    public:
        virtual void operator()(ast::BinaryExp& e) override;
        virtual void operator()(ast::Int& e) override;

    private:
        Emitter emitter_;
    };
}

#endif /* !COMPILER_HH_ */
