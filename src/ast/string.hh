#ifndef STRING_HH
# define STRING_HH

#include "visitor.hh"
#include "literal.hh"

namespace ast
{
    class String : public Literal
    {
        public:
            String(std::string value)
                : value_(value)
            {};

            virtual ~String()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::string get_value() const
            {
                return value_;
            };

            void set_value(std::string value)
            {
                value_ = value;
            }

        private:
            std::string value_;
    };
}

#endif /* STRING_HH */
