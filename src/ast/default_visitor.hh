#include "visitor.h"

namespace ast {
    class DefaultVisitor : public virtual Visitor {
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
            virtual void operator()(Operator& e) override;
            virtual void operator()(TypeIdentifier& e) override;
            virtual void operator()(TypePrototype& e) override;
            virtual void operator()(TypeStruct& e) override;
            virtual void operator()(TypeUnion& e) override;
            virtual void operator()(UnaryExp& e) override;
            virtual void operator()(Value& e) override;
            virtual void operator()(VarDec& e) override;
            virtual void operator()(WhileExp& e) override;
    };
}

#endif /* VISITOR_HH */
