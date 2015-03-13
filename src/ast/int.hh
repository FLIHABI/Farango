#ifndef INT_HH
# define INT_HH

#include "number.hh"

namespace ast
{
    class Int : public Number
    {
        public:
            Int();
            Int(int value)
                : value_(value)
            {};
            virtual ~Int();

            void virtual accept(Visitor& v);

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
