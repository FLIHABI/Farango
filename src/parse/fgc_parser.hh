#ifndef FGC_PARSER_HH
# define FGC_PARSER_HH

# include <memory>
# include "ast/ast_all.hh"

namespace parse
{
    class FgcParser
    {
        public:
            std::shared_ptr<ast::Ast> ast_;
    };
}

#endif /* FGC_PARSER_HH */
