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
            Register(std::vector<ast::FunctionDec*>&,
                     std::vector<ast::TypeStruct*>&,
                     std::vector<ast::TypeUnion*>&,
                     std::vector<ast::Id*>&,
                     std::vector<ast::String*>&);
            void process(ast::Ast&);
            virtual void operator()(ast::Ast& a) override;
            virtual void operator()(ast::FunctionDec& e) override;
            virtual void operator()(ast::TypeStruct& e) override;
            virtual void operator()(ast::TypeUnion& e) override;
            virtual void operator()(ast::TypeArray& e) override;
            virtual void operator()(ast::VarDec& e) override;
            virtual void operator()(ast::VarAssign& e) override;
            virtual void operator()(ast::AskExp& e) override;
            virtual void operator()(ast::String& e) override;

            inline uint16_t get_register_size()
            {
                return register_id_;
            }

        private:
            uint16_t type_id_ = 2;
            uint16_t register_id_ = 1; //reg 0 and 1 are used by compiler
            uint16_t function_id_ = 0;
            uint16_t ask_id_ = 0;
            std::vector<ast::FunctionDec*>& dec_;
            std::vector<ast::TypeStruct*>& struct_table_;
            std::vector<ast::TypeUnion*>& union_table_;
            std::vector<ast::Id*>& ask_table_;
            std::vector<ast::String*>& string_table_;
    };
}

#endif /* !REGISTER_HH */
