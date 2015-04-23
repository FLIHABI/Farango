#ifndef VARASSIGN_HH
# define VARASSIGN_HH

#include "vardec.hh"

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
