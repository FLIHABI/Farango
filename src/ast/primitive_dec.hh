#ifndef PRIMITIVE_DEC_HH
# define PRIMITIVE_DEC_HH

# include "declaration.hh"
# include "lib/symbol.hh"

namespace ast
{
    class IntDec : public Declaration
    {
        public:
            ~IntDec()
            {};

            static std::shared_ptr<IntDec> get_def()
            {
                static std::shared_ptr<IntDec> def = nullptr;
                if (!def)
                {
                    IntDec* d = new IntDec();
                    def = std::shared_ptr<IntDec>(d);
                }
                return def;
            }

        private:
            IntDec()
            {
                misc::symbol s("int");
                name_ = std::make_shared<Id>(s);
            }

    };
}

#endif /* PRIMITIVE_DEC_HH */
