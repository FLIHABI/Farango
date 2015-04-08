#include "all.hh"
#include "pretty_print.hh"
#include "lib/indent.hh"

namespace ast
{
    std::ostream& operator<<(std::ostream& out, Ast& ast)
    {
        PrettyPrinter p(out);
        p(ast);
        return out;
    }

    void PrettyPrinter::operator()(Ast& e)
    {
        DefaultVisitor::operator()(e);
    }

    void PrettyPrinter::operator()(AssignExp& e)
    {
        out_ << *e.lvalue_get() << " = " << *e.exp_get();
    }

    void PrettyPrinter::operator()(DoExp& e)
    {
        out_ << "do "
             << *e.body_get()
             << " while (" << *e.condition_get() << ")";
    }

    void PrettyPrinter::operator()(ExpList& e)
    {
        for (auto exp : e.list_get())
        {
            out_ << *exp << ";" << misc::iendl;
        }
    }

    void PrettyPrinter::operator()(ExpListFunction& e)
    {
        auto b = e.list_get().begin();
        auto end = e.list_get().end();
        while (b != end)
        {
            out_ << *b;
            out_ << (++b == end ? "" : ", ");
        }

    }

    void PrettyPrinter::operator()(ExpListInner& e)
    {
        out_ << misc::iendl << "{" << misc::incendl;
        for (auto exp : e.list_get())
        {
            out_ << *exp << ";" << misc::iendl;
        }
        out_ << misc::decendl << "}";
    }

    void PrettyPrinter::operator()(ForExp& e)
    {
        out_ << "for ("
             << *e.init_get() << "; "
             << *e.condition_get() << "; "
             << *e.end_get()
             << ")" << *e.body_get();
    }

    void PrettyPrinter::operator()(FunCall& e)
    {
        out_ << *e.value_get() << "(" << *e.list_get() << ")";
    }
}
