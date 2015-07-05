#ifndef ASK_EXP_HH
# define ASK_EXP_HH

# include <memory>

# include "fun_call.hh"
# include "value.hh"
# include "visitor.hh"


namespace ast
{
    class AskExp : public Value
    {
        public:
            AskExp(std::shared_ptr<FunCall> f)
                : f_(f)
            {};

            virtual ~AskExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<FunCall> f_get()
            {
                return f_;
            }

            inline uint16_t number_get() {
                return number_;
            }

            inline void number_set(const uint16_t num) {
                number_ = num;
            }

        private:
            std::shared_ptr<FunCall> f_;
            uint16_t number_;
    };
}

#endif /* ASK_EXP_HH */
