#include "parse/parse.hh"

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
    std::cout << *(fp.ast_);
}
