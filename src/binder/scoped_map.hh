#ifndef SCOPED_MAP_HH
# define SCOPED_MAP_HH

# include <map>
# include <memory>
# include <stack>

# include <ast/all.hh>
# include "lib/symbol.hh"

namespace binder
{
    class ScopedMap
    {
        public:
            ScopedMap()
            {};

            ~ScopedMap()
            {};

            void start_scop();
            void end_scop();

            void push_dec(std::shared_ptr<ast::VarDec> d);

            void push_dec(std::shared_ptr<ast::TypePrototype> d);
            void push_dec(std::shared_ptr<ast::TypeUnion> d);
            void push_dec(std::shared_ptr<ast::TypeStruct> d);

            void push_dec(std::shared_ptr<ast::FunctionDec> d);
            void push_dec(std::shared_ptr<ast::FunctionPrototype> d);

            std::shared_ptr<ast::Declaration> get_declaration(misc::symbol);

        private:
            std::map<misc::symbol, std::stack<std::pair<std::shared_ptr<ast::Declaration>, unsigned>>> map_;
            std::stack<misc::symbol> history_;
            unsigned age_;
    };
}

#endif /* SCOPED_MAP_HH */
