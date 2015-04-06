#ifndef FUNCTION_PROTOTPE_HH
# define FUNCTION_PROTOTPE_HH

# include <vector>

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

        protected:
            std::vector<VarDec> params_;
    };
}

#endif /* FunctionPrototype */
