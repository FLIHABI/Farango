#ifndef FUNCTION_PROTOTPE_HH
# define FUNCTION_PROTOTPE_HH

# include <vector>
# include <memory>

# include "ast_all.hh"
# include "declaration.hh"
# include "vardec.hh"
# include "visitor.hh"


namespace ast
{
    class FunctionPrototype : public Declaration
    {
        public:
            FunctionPrototype(Symbole name)
                : Declaration(name)
                , params_()
            {};

            FunctionPrototype(Symbole name, std::vector<VarDec> params)
                : Declaration(name)
                , params_(params)
            {};

            virtual ~FunctionPrototype()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::vector<VarDec>& params_get()
            {
                return params_;
            }

            std::shared_ptr<FunctionDec> func_dec_get()
            {
                return func_dec_;
            }

        protected:
            std::vector<VarDec> params_;
            std::shared_ptr<FunctionDec> func_dec_;
    };
}

#endif /* FunctionPrototype */
