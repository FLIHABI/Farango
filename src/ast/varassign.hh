#ifndef VARASSIGN_HH
# define VARASSIGN_HH

#include "lib/symbol.hh"
#include "vardec.hh"
#include "type_identifier.hh"

namespace ast
{
    class VarAssign : public VarDec
    {
        public:
            VarAssign(std::shared_ptr<VarDec> dec, std::shared_ptr<Exp> value)
                : VarDec(*dec)
                ,  value_(value)
            {
                decl_ = true;
            };

            VarAssign(misc::symbol name, misc::symbol type,
                      std::shared_ptr<Exp> value)
                : VarDec(std::make_shared<Id>(name),
                         std::make_shared<TypeIdentifierUse>(std::make_shared<Id>(type)))
                ,  value_(value)
            {
                decl_ = true;
            };

            virtual ~VarAssign()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> value_get()
            {
                return value_;
            }

        private:
            std::shared_ptr<Exp> value_;

    };
}

#endif /* VARASSIGN_HH */
