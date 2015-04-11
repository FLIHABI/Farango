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

            void push_dec(ast::Declaration& d);

            void push_dec(ast::TypeUnion& d);
            void push_dec(ast::TypeStruct& d);

            void push_dec(ast::FunctionDec& d);

            std::shared_ptr<ast::Declaration> get_s_declaration(misc::symbol);
            unsigned get_s_age(misc::symbol);

            unsigned get_age();

        private:
            template <typename T>
            void push_dec_p_(std::shared_ptr<T> t);

            std::map<misc::symbol, std::stack<std::pair<std::shared_ptr<ast::Declaration>, unsigned>>> map_;
            std::stack<misc::symbol> history_;
            unsigned age_;
    };
}

#endif /* SCOPED_MAP_HH */
