#ifndef REGISTER_HH
# define REGISTER_HH

# include <vector>

# include "ast/default_visitor.hh"
# include "ast/all.hh"

namespace compile {

    class FunctionRegister : public virtual ast::DefaultVisitor {
        using super = ast::DefaultVisitor;

        public:
            FunctionRegister(std::vector<ast::FunctionDec*>& dec);
            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::FunctionDec& e) override;

        private:
            std::vector<ast::FunctionDec*>& dec_;
    };

    class Register : public virtual ast::DefaultVisitor {
        using super = ast::DefaultVisitor;

        public:
            Register(std::vector<ast::FunctionDec*>& dec);
            void process(ast::Ast&);
            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::FunctionDec& e) override;
            virtual void operator()(ast::TypeStruct& e) override;
            virtual void operator()(ast::TypeUnion& e) override;
            virtual void operator()(ast::VarDec& e) override;
            virtual void operator()(ast::VarAssign& e) override;

        private:
            uint16_t type_id_ = 0;
            uint16_t register_id_ = 1; //reg 0 is used by compiler
            uint16_t function_id_ = 0;
            std::vector<ast::FunctionDec*>& dec_;
    };
}

#endif /* !REGISTER_HH */
