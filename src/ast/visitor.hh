#ifndef VISITOR_HH
# define VISITOR_HH

#include "ast_all.hh"

namespace ast
{
    class Visitor
    {
        public:
            Visitor();
            virtual ~Visitor();

            virtual void operator()(Ast& a) = 0;
            virtual void operator()(Exp& e) = 0;
            virtual void operator()(ExpList& e) = 0;
            virtual void operator()(FunCall& e) = 0;
            virtual void operator()(BinaryExp& e) = 0;
            virtual void operator()(Lvalue& e) = 0;
            virtual void operator()(MemberAccess& e) = 0;
            virtual void operator()(AssignExp& e) = 0;
            virtual void operator()(UnaryExp& e) = 0;
            virtual void operator()(IfExp& e) = 0;
            virtual void operator()(DoExp& e) = 0;
            virtual void operator()(WhileExp& e) = 0;
            virtual void operator()(Declaration& e) = 0;
            virtual void operator()(VarDec& e) = 0;
            virtual void operator()(FunctionPrototype& e) = 0;
            virtual void operator()(FunctionDec& e) = 0;
            virtual void operator()(TypeIdentifier& e) = 0;
            virtual void operator()(TypePrototype& e) = 0;
            virtual void operator()(TypeStruct& e) = 0;
            virtual void operator()(TypeUnion& e) = 0;
    };
} //ast

#endif /* VISITOR_HH */
