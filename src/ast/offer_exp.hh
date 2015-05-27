#ifndef OFFER_EXP_HH
# define OFFER_EXP_HH

# include <memory>

# include "fun_call.hh"
# include "value.hh"
# include "visitor.hh"


namespace ast
{
    class OfferExp : public Value
    {
        public:
            OfferExp(std::shared_ptr<FunCall> f)
                : f_(f)
            {};

            virtual ~OfferExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<FunCall> f_get()
            {
                return f_;
            }

        private:
            std::shared_ptr<FunCall> f_;
    };
}

#endif /* OFFER_HH */
