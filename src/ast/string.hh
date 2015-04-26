#ifndef STRING_HH
# define STRING_HH

#include "visitor.hh"
#include "literal.hh"
#include "primitive_dec.hh"

namespace ast
{
    class String : public Literal
    {
        public:
            String(std::string value)
                : value_(value)
            {
               type_value_set(StringDec::get_def());
            };

            virtual ~String()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::string value_get() const
            {
                return value_;
            };

            void value_get(std::string value)
            {
                value_ = value;
            }

        private:
            std::string value_;
    };
}

#endif /* STRING_HH */
