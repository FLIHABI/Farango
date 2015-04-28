#ifndef FGC_PARSER_HH
# define FGC_PARSER_HH

# include <memory>
# include "location.hh"
# include "ast/ast_all.hh"

namespace parse
{
    class FgcParser
    {
        public:
            void parse(FILE* in);
            std::shared_ptr<ast::Ast> ast_;
            yy::location l_;

    };
}

#endif /* FGC_PARSER_HH */
