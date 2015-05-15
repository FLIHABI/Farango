#ifndef ARRAY_ACCESS_HH
# define ARRAY_ACCESS_HH

# include <memory>

# include "lvalue.hh"
# include "visitor.hh"

namespace ast
{
    class ArrayAccess : public Value
    {
        public:
            ArrayAccess(std::shared_ptr<Value> val, std::shared_ptr<Exp> offset)
                : val_(val)
                , offset_(offset)
            {};

            virtual ~ArrayAccess()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Value> val_get()
            {
                return val_;
            }

            std::shared_ptr<Exp> offset_get()
            {
                return offset_;
            }

        private:
            std::shared_ptr<Value> val_;
            std::shared_ptr<Exp> offset_;
    };
}

#endif /* ARRAY_ACCESS_HH */
