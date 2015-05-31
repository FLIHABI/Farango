#ifndef GET_EXP_HH
# define GET_EXP_HH

# include <memory>

# include "fun_call.hh"
# include "value.hh"
# include "visitor.hh"


namespace ast
{
    class GetExp : public Value
    {
        public:
            GetExp(std::shared_ptr<Value> v)
                : value_(v)
            {};

            virtual ~GetExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Value> value_get()
            {
                return value_;
            }

        private:
            std::shared_ptr<Value> value_;

    };
}

#endif /* GET_EXP_HH */
