#ifndef FUN_CALL_HH
# define FUN_CALL_HH

# include <memory>
# include "value.hh"
# include "visitor.hh"

namespace ast
{
    class FunCall : public Value
    {
        public:
            FunCall(std::shared_ptr<Value> value, std::shared_ptr<ExpList> list)
                : value_(value)
                , list_(list)
            {};
            virtual ~FunCall();

            void virtual accept(Visitor& v)
            {
                v(*this);
            }
            
            std::shared_ptr<Value> get_value()
            {
                return value_;
            }

            std::shared_ptr<ExpList> get_list()
            {
                return list_;
            }

        private:
            std::shared_ptr<Value> value_;
            std::shared_ptr<ExpList> list_; //Using explist in function, FIXME later ?
    };
}

#endif /* FUN_CALL_HH */