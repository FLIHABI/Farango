#ifndef INT_HH
# define INT_HH

#include "visitor.hh"
#include "number.hh"

namespace ast
{
    class Int : public Number
    {
        public:
            Int(int value)
                : value_(value)
            {};
            virtual ~Int()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            int get_value() const
            {
                return value_;
            };

            void set_value(int value)
            {
                value_ = value;
            }

        private:
            int value_;
    };
}

#endif /* INT_HH */
