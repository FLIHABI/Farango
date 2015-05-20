#ifndef DECLARATION_HH
# define DECLARATION_HH

# include "exp.hh"
# include "id.hh"
# include "visitor.hh"

namespace ast
{
    class Declaration : public Exp
    {
        public:
            Declaration(std::shared_ptr<Id> name)
                : name_(name)
            {};
            virtual ~Declaration()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            virtual std::shared_ptr<Id>& name_get()
            {
                return name_;
            }

            inline uint16_t number_get() {
                return number_;
            }

            inline void number_set(const uint16_t num) {
                number_ = num;
            }

        protected:
            Declaration()
            {};
            std::shared_ptr<Id> name_;
            uint16_t number_;
    };
}
#endif /* DECLARATION_HH */
