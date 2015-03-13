#ifndef LITERAL_HH
# define LITERAL_HH

#include "value.hh"

namespace ast
{
    class Literal : public Value
    {
        public:
            Literal();
            virtual ~Literal();

            void virtual accept(Visitor& v) = 0;
    };
}

#endif /* LITERAL_HH */
