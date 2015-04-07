#ifndef NUMBER_HH
# define NUMBER_HH

#include "literal.hh"

namespace ast
{
    class Number : public Literal
    {
        public:
            Number()
            {};
            virtual ~Number()
            {};

            void virtual accept(Visitor& v) = 0;
    };
}

#endif /* NUMBER_HH */
