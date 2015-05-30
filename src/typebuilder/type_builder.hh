#ifndef TYPE_BUILDER_HH
# define TYPE_BUILDER_HH

# include <map>
# include <memory>

# include "ast/all.hh"
# include "ast/default_visitor.hh"
# include "lib/error.hh"

namespace typebuilder
{
    class TypeBuilder : public ast::DefaultVisitor
    {
        using super = ast::DefaultVisitor;

        public:
            TypeBuilder(misc::error& e);
            virtual ~TypeBuilder();

            virtual void operator()(ast::Ast& a);
            virtual void operator()(ast::TypeArrayIdentifier& e);
            virtual void operator()(ast::TypeIdentifierUse& e);
        private:
            void build_struct(std::shared_ptr<ast::TypeStruct>,
                              ast::TypeIdentifierUse&,
                              std::map<misc::symbol, std::shared_ptr<ast::TypeIdentifierUse>>&);
            misc::error& e_;
    };
}

#endif /* TYPE_BUILDER_HH  */
