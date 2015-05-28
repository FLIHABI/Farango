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
                , value_(value)
                , vardec_(dec)
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

            std::shared_ptr<VarDec> vardec_get()
            {
                return vardec_;
            }

        private:
            std::shared_ptr<Exp> value_;
            std::shared_ptr<VarDec> vardec_;

    };
}

#endif /* VARASSIGN_HH */
