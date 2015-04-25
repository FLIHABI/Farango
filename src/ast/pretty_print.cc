#include "all.hh"
#include "pretty_print.hh"
#include "lib/indent.hh"

namespace ast
{
    std::string op_print[] = {
        "+",
        "-",
        "*",
        "/",
        "==",
        "!=",
        "&",
        "|",
        "^",
        "&&",
        "||",
        ">",
        ">=",
        "<",
        "<=",
        "!",
        "~"
    };

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
            out_ << **b;
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
        out_ << *e.value_get();
        if (e.generics_instance_get().size() > 0)
        {
            out_ << "::<";
            auto b = e.generics_instance_get().begin();
            auto end = e.generics_instance_get().end();
            while (b != end)
            {
                out_ << **b;
                out_ << (++b == end ? ">" : ", ");
            }
        }
        out_ << "(" << *e.list_get() << ")";
    }

    void PrettyPrinter::operator()(FunctionDec& e)
    {
        out_ << "fun " << *e.name_get();

        if (e.generics_get().size() > 0)
        {
            out_ << "<";
            auto b = e.generics_get().begin();
            auto end = e.generics_get().end();
            while (b != end)
            {
                out_ << *(*b)->name_get();
                out_ << (++b == end ? ">" : ", ");
            }
        }

        out_ << "(";
        auto b = e.params_get().begin();
        auto end = e.params_get().end();
        while (b != end)
        {
            out_ << *b;
            out_ << (++b == end ? "" : ", ");
        }
        out_ << ")";
        if (e.return_t_get())
            out_ << " : " << *e.return_t_get();
        out_ << " = " << *e.body_get();
        out_ << " /* declared at " << e.type_dec_get() << " */ ";
    }

    void PrettyPrinter::operator()(FunctionPrototype& e)
    {
        out_ << "fun " << *e.name_get();

        if (e.generics_get().size() > 0)
        {
            out_ << "<";
            auto b = e.generics_get().begin();
            auto end = e.generics_get().end();
            while (b != end)
            {
                out_ << *(*b)->name_get();
                out_ << (++b == end ? ">" : ", ");
            }
        }

        out_ << "(";

        auto b = e.params_get().begin();
        auto end = e.params_get().end();
        while (b != end)
        {
            out_ << *b;
            out_ << (++b == end ? "" : ", ");
        }
        out_ << ")";
        if (e.return_t_get())
            out_ << " : " << *e.return_t_get();
        out_ << " /* declared at " << e.type_dec_get() << " */ ";
    }

    void PrettyPrinter::operator()(IfExp& e)
    {
        out_ << "if (" << *e.if_get() << ") "
             <<  *e.then_get();
        if (e.else_get())
            out_ << " else" << *e.else_get();
    }

    void PrettyPrinter::operator()(Int& e)
    {
        out_ << e.value_get();
    }

    void PrettyPrinter::operator()(Lvalue& e)
    {
        out_ << *e.s_get();
    }

    void PrettyPrinter::operator()(MemberAccess& e)
    {
        out_ << *e.lval_get() << "." << *e.s_get();
    }

    void PrettyPrinter::operator()(TypeIdentifierUse& e)
    {
        out_ << *e.type_name_get();
        if (e.specs_get().size() == 0)
            return;
        else if (e.specs_get().size() == 1)
            out_ << " " << *e.specs_get()[0];

        else
        {
            auto b = e.specs_get().begin();
            auto end = e.specs_get().end();
            out_ << " (";
            while (b != end)
            {
                out_ << *b;
                out_ << (++b == end ? "" : ", ");
            }
            out_ << ")";
        }
    }

    void PrettyPrinter::operator()(TypeIdentifierDec& e)
    {
        out_ << *e.type_name_get();
        if (e.specs_get().size() == 0)
            return;
        else if (e.specs_get().size() == 1)
            out_ << " " << *e.specs_get()[0];

        else
        {
            auto b = e.specs_get().begin();
            auto end = e.specs_get().end();
            out_ << " (";
            while (b != end)
            {
                out_ << *(*b)->name_get();
                out_ << (++b == end ? "" : ", ");
            }
            out_ << ")";
        }
    }

    void PrettyPrinter::operator()(TypePrototype& e)
    {
        out_ << "type " << *e.type_get()
             << " /* declared at " << e.type_dec_get() << " */ ";
    }

    void PrettyPrinter::operator()(TypeStruct& e)
    {
        out_ << "type " << *e.type_get() << " = {" << misc::incendl;
        for (auto& v : e.members_get())
        {
            out_ << v << ";" << misc::iendl;
        }
        out_ << misc::decendl<< "}"
             << " /* declared at " << e.type_dec_get() << " */ ";
    }

    void PrettyPrinter::operator()(TypeUnion& e)
    {
        out_ << "type " << *e.type_get() << " =" << misc::incendl;
        auto b = e.unions_get().begin();
        auto end = e.unions_get().end();
        while (b != end)
        {
            out_ << *b;
            out_ << misc::iendl << (++b == end ? "" : "| ");
        }
        out_ << misc::decendl;
        out_ << " /* declared at " << e.type_dec_get() << " */ ";
    }

    void PrettyPrinter::operator()(VarDec& e)
    {
        if (e.decl_get())
            out_ << "var ";
        out_ << *e.name_get() << " : " << *e.type_get();
    }

    void PrettyPrinter::operator()(VarAssign& e)
    {
        out_ << "var ";
        out_ << *e.name_get() << " : " << *e.type_get();
        out_ << " = " << *e.value_get();
    }

    void PrettyPrinter::operator()(WhileExp& e)
    {
        out_ << "while (" << *e.condition_get() << ") "
             << *e.body_get();
    }

    void PrettyPrinter::operator()(String& e)
    {
        out_ << "\"" << e.value_get() << "\"";
    }

    void PrettyPrinter::operator()(InnerExp& e)
    {
        out_ << "(" << *e.exp_get() << ")";
    }

    void PrettyPrinter::operator()(BinaryExp& e)
    {
        //FIXME, ugly
        out_ << *e.valuel_get()
             << " " << op_print[e.op_get()] << " "
             << *e.expr_get();
    }

    void PrettyPrinter::operator()(UnaryExp& e)
    {
        //FIXME, ugly
        out_ << op_print[e.op_get()] << *e.exp_get();
    }

    void PrettyPrinter::operator()(Id& e)
    {
        out_ << e.s_get() << " /* " << e.dec_get() << " */ ";
    }
}
