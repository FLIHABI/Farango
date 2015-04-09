#ifndef VARDEC_HH
# define VARDEC_HH

# include <vector>
# include <memory>

# include "type_identifier.hh"
# include "declaration.hh"
# include "visitor.hh"

namespace ast
{
    class VarDec : public Declaration
    {
        public:
            VarDec(Symbole name, std::shared_ptr<TypeIdentifier> type)
                : Declaration(name)
                , type_(type)
            {};

            virtual ~VarDec()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<TypeIdentifier> type_get()
            {
                return type_;
            }

            void decl_set(bool b)
            {
                decl_ = b;
            }

            bool decl_get()
            {
                return decl_;
            }

        protected:
            std::shared_ptr<TypeIdentifier> type_;
            bool decl_ = false;
    };
}

#endif /* VARDEC_HH */
