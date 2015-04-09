#ifndef DEFAULT_VISITOR_HH
# define DEFAULT_VISITOR_HH

# include "visitor.hh"

namespace ast
{
    class DefaultVisitor : public virtual Visitor
    {
        public:
            using Visitor::operator();

            DefaultVisitor();
            virtual ~DefaultVisitor();

            virtual void operator()(AssignExp& e) override;
            virtual void operator()(Ast& a) override;
            virtual void operator()(BinaryExp& e) override;
            virtual void operator()(Declaration& e) override;
            virtual void operator()(DoExp& e) override;
            virtual void operator()(Exp& e) override;
            virtual void operator()(ExpList& e) override;
            virtual void operator()(ForExp& e) override;
            virtual void operator()(FunCall& e) override;
            virtual void operator()(FunctionDec& e) override;
            virtual void operator()(FunctionPrototype& e) override;
            virtual void operator()(IfExp& e) override;
            virtual void operator()(Int& e) override;
            virtual void operator()(Literal& e) override;
            virtual void operator()(Lvalue& e) override;
            virtual void operator()(MemberAccess& e) override;
            virtual void operator()(Number& e) override;
            virtual void operator()(TypeIdentifier& e) override;
            virtual void operator()(TypePrototype& e) override;
            virtual void operator()(TypeStruct& e) override;
            virtual void operator()(TypeUnion& e) override;
            virtual void operator()(UnaryExp& e) override;
            virtual void operator()(Value& e) override;
            virtual void operator()(VarDec& e) override;
            virtual void operator()(WhileExp& e) override;
            virtual void operator()(String& e) override;
            virtual void operator()(InnerExp& e) override;
            virtual void operator()(ExpListInner& e) override;
            virtual void operator()(ExpListFunction& e) override;
            virtual void operator()(Id& e) override;
    };
}
#endif /* DEFAULT_VISITOR_HH */
