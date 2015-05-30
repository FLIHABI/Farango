#ifndef FUN_CALL_HH
# define FUN_CALL_HH

# include <memory>
# include <vector>
# include "value.hh"
# include "visitor.hh"

namespace ast
{
    class FunCall : public Value
    {
        public:
            FunCall(std::shared_ptr<Value> value, std::vector<std::shared_ptr<TypeIdentifierUse>> generics_instance ,std::shared_ptr<ExpListFunction> list)
                : value_(value)
                , generics_instance_(generics_instance)
                , list_(list)
            {};

            virtual ~FunCall()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Value> value_get()
            {
                return value_;
            }

            std::vector<std::shared_ptr<TypeIdentifierUse>>& generics_instance_get()
            {
                return generics_instance_;
            }

            std::shared_ptr<ExpListFunction> list_get()
            {
                return list_;
            }

            std::shared_ptr<FunctionDec> func_get()
            {
                return func_;
            }


            void func_set(std::shared_ptr<FunctionDec> func)
            {
                func_ = func;
            }

        private:
            std::shared_ptr<Value> value_;
            std::vector<std::shared_ptr<TypeIdentifierUse>> generics_instance_;
            std::shared_ptr<ExpListFunction> list_; //Using explist in function, FIXME later ?
            std::shared_ptr<FunctionDec> func_;
    };
}

#endif /* FUN_CALL_HH */
