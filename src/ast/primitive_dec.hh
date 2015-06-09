#ifndef PRIMITIVE_DEC_HH
# define PRIMITIVE_DEC_HH

# include "lib/symbol.hh"

# include "ast_all.hh"
# include "declaration.hh"
# include "type_value.hh"
# include "type_identifier.hh"
# include "type_struct.hh"

/* FIXME
 * Reffactor with template
 */

namespace ast
{
    class IntDec : public TypeValue
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
                number_ = 0;
                misc::symbol s("int");
                name_ = std::make_shared<Id>(s);
            }

    };

    class VoidDec : public TypeValue
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

    class StringDec : public TypeValue
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

    class NullDec : public TypeValue
    {
        public:
            ~NullDec()
            {};

            static std::shared_ptr<NullDec> get_def()
            {
                static std::shared_ptr<NullDec> def = nullptr;
                if (!def)
                {
                    NullDec* d = new NullDec();
                    def = std::shared_ptr<NullDec>(d);
                }
                return def;
            }

        private:
            NullDec()
            {
                misc::symbol s("null");
                name_ = std::make_shared<Id>(s);
            }

    };

    class AutoDec : public TypeValue
    {
        public:
            ~AutoDec()
            {};

            static std::shared_ptr<AutoDec> get_def()
            {
                static std::shared_ptr<AutoDec> def = nullptr;
                if (!def)
                {
                    AutoDec* d = new AutoDec();
                    def = std::shared_ptr<AutoDec>(d);
                }
                return def;
            }

        private:
            AutoDec()
            {
                misc::symbol s("auto");
                name_ = std::make_shared<Id>(s);
            }

    };

    /*
     * Used by offer and get
     */
    class GetDec : public TypeStruct
    {
        public:
            static std::shared_ptr<GetDec> get_def()
            {
                static std::shared_ptr<GetDec> def = nullptr;
                if (!def)
                {
                    GetDec* d = new GetDec(
                            );
                    def = std::shared_ptr<GetDec>(d);
                }
                return def;
            }

            GetDec(std::shared_ptr<TypeIdentifierDec> dec)
                : TypeStruct(dec)
            {};

        private:
            GetDec()
                : TypeStruct(
                        std::make_shared<TypeIdentifierDec>(std::make_shared<ast::Id>("lol")
                        ))
            {
              number_ = 1;
               type_get()->specs_get().push_back(
                       std::make_shared<ast::Declaration>(std::make_shared<ast::Id>("A"))
                       );
            };
    };
}

#endif /* PRIMITIVE_DEC_HH */
