#ifndef OPERATOR_HH
# define OPERATOR_HH

# include <string>

namespace ast
{
    enum Operator
    {
        PLUS,
        MINUS,
        MUL,
        DIV,
        EQUAL,
        NEQUAL,
        AND,
        OR,
        XOR,
        LAND,
        LOR,
        GREATER,
        GREATER_EQ,
        LESS,
        LESS_EQ,
        BANG,
        TILDE,
    };

}

#endif /* OPERATOR_HH */
