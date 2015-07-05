#ifndef ID_HH
# define ID_HH

# include <memory>

# include "lib/symbol.hh"

# include "ast.hh"
# include "declaration.hh"
# include "visitor.hh"


namespace ast
{
    class Id : public Ast
    {
        public:
            Id(misc::symbol s)
                : s_(s)
            {};
            virtual ~Id()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            misc::symbol s_get() const
            {
                return s_;
            };

            std::shared_ptr<Declaration> dec_get()
            {
                return dec_;
            };

            void dec_change(std::shared_ptr<Declaration> dec)
            {
                dec_ = dec;
            };

            void dec_set(std::shared_ptr<Declaration> d)
            {
                dec_ = d;
            };

            inline uint16_t number_get() {
                return number_;
            }

            inline void number_set(const uint16_t num) {
                number_ = num;
            }

        private:
            misc::symbol s_;
            std::shared_ptr<Declaration> dec_;
            uint16_t number_;

    };
}

#endif /* ID_HH */
