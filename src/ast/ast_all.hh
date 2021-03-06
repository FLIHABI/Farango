#ifndef AST_ALL_HH
# define AST_ALL_HH

/*
 * Operator *
 * Ast *
 *  TypeIdentifier *
 *  Exp *
 *   ExpList *
 *   AssignExp *
 *   Value *
 *    FunCall *
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
    class TypePrototype;
    class TypeStruct;
    class TypeUnion;
    class TypeArray;
    class String;
    class InnerExp;
    class ForExp;
    class Int;
    class Number;
    class ExpListInner;
    class ExpListFunction;
    class Id;
    class VarAssign;
    template <typename T>
    class TypeIdentifier;
    class TypeIdentifierUse;
    class TypeFunctionIdentifier;

    using TypeIdentifierDec = TypeIdentifier<Declaration>;

    class Visitor;
    class LoopExp;
    class BreakExp;
    class ContinueExp;
    class ArrayAccess;
    class TypeArrayIdentifier;
    class NewExp;
    class TypeValue;
    class OfferExp;
    class GetExp;
    class AskExp;

}

#endif /* AST_ALL_HH */
