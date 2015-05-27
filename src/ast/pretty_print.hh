/*
 * Use to test visitor
 */

#ifndef PRETTY_PRINT_HH
# define PRETTY_PRINT_HH

# include <iostream>

# include "default_visitor.hh"
# include "lib/error.hh"

namespace ast
{
    class PrettyPrinter : public DefaultVisitor
    {
        public:
            PrettyPrinter(std::ostream& o)
                : out_(o)
            {};

            ~PrettyPrinter()
            {};

            virtual void operator()(AssignExp& e) override;
            virtual void operator()(Ast& a) override;

            virtual void operator()(BinaryExp& e) override;
            virtual void operator()(UnaryExp& e) override;

            virtual void operator()(DoExp& e) override;
            virtual void operator()(ExpList& e) override;
            virtual void operator()(ExpListFunction& e) override;
            virtual void operator()(ExpListInner& e) override;
            virtual void operator()(ForExp& e) override;
            virtual void operator()(FunCall& e) override;

            virtual void operator()(FunctionDec& e) override;
            virtual void operator()(FunctionPrototype& e) override;
            virtual void operator()(IfExp& e) override;
            virtual void operator()(Int& e) override;
            virtual void operator()(Lvalue& e) override;
            virtual void operator()(MemberAccess& e) override;
            virtual void operator()(TypeIdentifierDec& e) override;
            virtual void operator()(TypeIdentifierUse& e) override;
            virtual void operator()(TypePrototype& e) override;
            virtual void operator()(TypeStruct& e) override;
            virtual void operator()(TypeUnion& e) override;
            virtual void operator()(VarDec& e) override;
            virtual void operator()(VarAssign& e) override;
            virtual void operator()(WhileExp& e) override;
            virtual void operator()(String& e) override;
            virtual void operator()(InnerExp& e) override;
            virtual void operator()(Id& e) override;

            virtual void operator()(BreakExp& e) override;
            virtual void operator()(ContinueExp& e) override;
            virtual void operator()(ArrayAccess& e) override;
            virtual void operator()(TypeArrayIdentifier& e) override;
            virtual void operator()(NewExp& e) override;
            virtual void operator()(OfferExp& e) override;

        private:
            std::ostream& out_;

    };

    std::ostream& operator<<(std::ostream& out, Ast& ast);
    misc::error& operator<<(misc::error& out, Ast& ast);
}

#endif /* PRETTY_PRINT_HH */
