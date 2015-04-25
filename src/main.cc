#include "parse/parse.hh"
#include "binder/binder.hh"
#include "ast/pretty_print.hh"
#include "compile/compiler.hh"

void yy::parser::error(const std::string& msg) {
    std::cerr << msg << std::endl;
    exit(3);
}

int main (int argc, char **argv) {
    parse::FgcParser fp;
    FILE* in = stdin;
    if (argc > 1)
        in = fopen(argv[1], "r");
    fp.parse(in);

    misc::error e;
    binder::Binder b(e);

    b(*fp.ast_);

    std::cout << e;

    std::cout << *fp.ast_;

    /*
    compile::Compile c;

    c(*fp.ast_);

    c.write("out.fge");
    */
}
