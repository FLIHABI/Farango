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
            VarDec(std::shared_ptr<Id> name, std::shared_ptr<TypeIdentifierUse> type)
                : Declaration(name)
                , type_(type)
            {};

            virtual ~VarDec()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<TypeIdentifierUse> type_get()
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

            inline uint16_t register_number_get() {
                return register_number_;
            }

            inline void register_number_set(const uint16_t num) {
                register_number_ = num;
            }

        protected:
            std::shared_ptr<TypeIdentifierUse> type_;
            bool decl_ = false;
            uint16_t register_number_;
    };
}

#endif /* VARDEC_HH */
