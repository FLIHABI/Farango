#ifndef AST_ALL_HH
# define AST_ALL_HH

/*
 * Operator *
 * Ast *
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
 *    TypeDec
 *
 */

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

    class Visitor;

    class Symbole; //from misc, FIXME
}

#endif /* AST_ALL_HH */
