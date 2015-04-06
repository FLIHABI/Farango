#ifndef DECLARATION_HHj
# define DECLARATION_HH

# include "exp.hh"
# include "visitor.hh"

namespace ast
{
    class Declaration : public Exp
    {
        public:
            Declaration(Symbole name)
                : name_(name)
            {};
            virtual ~Declaration()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            Symbole name_get()
            {
                return name_;
            }

        protected:
            Symbole name_;

    };
}
#endif /* DECLARATION_HH */
