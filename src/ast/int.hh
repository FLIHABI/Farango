#ifndef INT_HH
# define INT_HH

# include "visitor.hh"
# include "number.hh"
# include "primitive_dec.hh"

namespace ast
{
    class Int : public Number
    {
        public:
            Int(int value)
                : value_(value)
            {
                type_value_ = IntDec::get_def();
            };
            virtual ~Int()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            int value_get() const
            {
                return value_;
            };

            void value_set(int value)
            {
                value_ = value;
            }

        private:
            int value_;
    };
}

#endif /* INT_HH */
