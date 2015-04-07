#ifndef VALUE_HH
# define VALUE_HH

#include "exp.hh"

namespace ast
{
    class Value : public Exp
    {
        public:
            Value()
            {};
            virtual ~Value()
            {};

            void virtual accept(Visitor& v) = 0;
    };
}

#endif /* VALUE_HH */
