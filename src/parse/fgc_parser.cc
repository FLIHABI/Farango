#include "parse/fgc_parser.hh"
#include "parse/parse.hh"

namespace parse
{
    void FgcParser::parse(FILE* in)
    {
        yyin = in;
        yy::parser p(*this);
        p.set_debug_level(1);
        p.parse();
    }
}
