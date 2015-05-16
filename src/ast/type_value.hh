#ifndef TYPE_VALUE_HH
# define TYPE_VALUE_HH

# include "declaration.hh"
# include "visitor.hh"

namespace ast
{
    class TypeValue : public Declaration
    {
        public:
            TypeValue()
            {};

            virtual ~TypeValue()
            {
            };

            void virtual accept(Visitor& v)
            {
                v(*this);
            }
   };
}
#endif /* TYPE_VALUE_HH */
