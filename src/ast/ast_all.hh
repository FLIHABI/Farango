#ifndef AST_ALL_HH
# define AST_ALL_HH

/*
 * Operator *
 * Ast *
 *  TypeIdentifier * //FIXME:Need change to differencies creation and instantiation (genericity)
 *  Exp *
 *   ExpList *
 *   AssignExp *
 *   Value *
 *    FunCall *
 *    Literal *
 *    BinaryExp *
 *    Lvalue .
 *    MemberAccess .
 *    Literal *
 *     String
 *     Number *
 *      Int *
 *      Double
 *   Declaration*
 *    TypePrototype *
 *     TypeStruct *
 *    VarDec *
 *    FunctionPrototype *
 *     FunctionDec *
 *
 */

# include "lib/symbol.hh"

namespace ast
{
    class Ast;
    class Exp;
    class ExpList;
    class Value;
    class Literal;
    class FunCall;
    class ParamList;
    class BinaryExp;
    class Lvalue; //FIXME, symbole
    class MemberAccess; //FIXME, symbole
    class AssignExp;
    class UnaryExp;
    class IfExp;
    class DoExp;
    class WhileExp;
    class Declaration;
    class VarDec;
    class FunctionPrototype;
    class FunctionDec;
    class TypeIdentifier;
    class TypePrototype;
    class TypeStruct;
    class TypeUnion;

    class Visitor;
    using Symbole = misc::symbol;
}

#endif /* AST_ALL_HH */
