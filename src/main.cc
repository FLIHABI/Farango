#include "parse/parse.hh"
#include "ast/pretty_print.hh"
#include "binder/binder.hh"
#include "typebuilder/type_builder.hh"
#include "typechecker/type_checker.hh"
#include "compile/compiler.hh"

int main (int argc, char **argv) {
    parse::FgcParser fp;
    FILE* in = stdin;
    if (argc > 1)
        in = fopen(argv[1], "r");
    fp.parse(in);

    misc::error e;
    binder::Binder b(e);

    b(*fp.ast_);
    if (e.status_get())
    {
        std::cerr << e;
        return e.status_get();
    }


    typebuilder::TypeBuilder tb(e);
    tb(*fp.ast_);

    if (e.status_get())
    {
        std::cerr << e;
        return e.status_get();
    }

    typechecker::TypeChecker t(e);
    t(*fp.ast_);

    if (e.status_get())
    {
        std::cerr << e;
        return e.status_get();
    }


    std::cout << *fp.ast_;

    compile::Compile c;

    c(*fp.ast_);

    c.write("out.fge");
}
