#ifndef PRIMITIVE_DEC_HH
# define PRIMITIVE_DEC_HH

# include "declaration.hh"
# include "lib/symbol.hh"

/* FIXME
 * Reffactor with template
 */

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

    class VoidDec : public Declaration
    {
        public:
            ~VoidDec()
            {};

            static std::shared_ptr<VoidDec> get_def()
            {
                static std::shared_ptr<VoidDec> def = nullptr;
                if (!def)
                {
                    VoidDec* d = new VoidDec();
                    def = std::shared_ptr<VoidDec>(d);
                }
                return def;
            }

        private:
            VoidDec()
            {
                misc::symbol s("void");
                name_ = std::make_shared<Id>(s);
            }

    };

    class StringDec : public Declaration
    {
        public:
            ~StringDec()
            {};

            static std::shared_ptr<StringDec> get_def()
            {
                static std::shared_ptr<StringDec> def = nullptr;
                if (!def)
                {
                    StringDec* d = new StringDec();
                    def = std::shared_ptr<StringDec>(d);
                }
                return def;
            }

        private:
            StringDec()
            {
                misc::symbol s("string");
                name_ = std::make_shared<Id>(s);
            }

    };
}

#endif /* PRIMITIVE_DEC_HH */
