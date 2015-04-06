#ifndef TYPE_IDENTIFIER_HH
# define TYPE_IDENTIFIER_HH

#include <vector>

#include "ast.hh"
#include "visitor.hh"

namespace ast
{
    class TypeIdentifier : public Ast
    {
        public:
            TypeIdentifier(Symbole type_name, std::vector<Symbole> specs)
                : type_name_(type_name)
                , specs_(specs)
            {};

            TypeIdentifier(Symbole type_name)
                : type_name_(type_name)
            {};

            virtual ~TypeIdentifier()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            Symbole& type_name_get()
            {
                return type_name_;
            }

            std::vector<Symbole>& specs_get()
            {
                return specs_;
            }

        private:
            Symbole type_name_;
            std::vector<Symbole> specs_;
    };
}

#endif /* TYPE_IDENTIFIER_HH */
