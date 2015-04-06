#ifndef VARDEC_HH
# define VARDEC_HH

# include "declaration.hh"
# include "visitor.hh"

namespace ast
{
    class VarDec : Declaration
    {
        public:
            VarDec(Symbole name, Symbole type)
                : Declaration(name)
                , type_(type)
            {};

            virtual ~VarDec()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            Symbole type_get()
            {
                return type_;
            }

        protected:
            Symbole type_;
    };
}

#endif /* VARDEC_HH */
