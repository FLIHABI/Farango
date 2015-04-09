#ifndef FUNCTION_DEC_HH
# define FUNCTION_DEC_HH


# include <memory>

# include "exp.hh"
# include "vardec.hh"
# include "function_prototype.hh"
# include "visitor.hh"

namespace ast
{
    class FunctionDec : public FunctionPrototype
    {
        public:
            FunctionDec(std::shared_ptr<Id> name, std::shared_ptr<Exp> body)
                : FunctionPrototype(name)
                , body_(body)
            {};

            FunctionDec(std::shared_ptr<Id> name, std::vector<VarDec> params,
                    std::shared_ptr<Exp> body)
                : FunctionPrototype(name, params)
                , body_(body)
            {};

            FunctionDec(FunctionPrototype& f, std::shared_ptr<Exp> body)
                : FunctionPrototype(f)
                , body_(body)
            {};

            virtual ~FunctionDec()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Exp> body_get()
            {
                return body_;
            }

        private:
            std::shared_ptr<Exp> body_;

    };
}

#endif /* FUNCTION_DEC_HH */
