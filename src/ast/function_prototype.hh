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
            FunctionPrototype(std::shared_ptr<Id> name, std::vector<std::shared_ptr<Declaration>> generic, std::vector<VarDec> params, std::shared_ptr<TypeIdentifierUse> return_t)
                : Declaration(name)
                , generics_(generic)
                , params_(params)
                , return_t_(return_t)
            {};

            virtual ~FunctionPrototype()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::vector<std::shared_ptr<Declaration>>& generics_get()
            {
                return generics_;
            }

            std::vector<VarDec>& params_get()
            {
                return params_;
            }

            std::shared_ptr<TypePrototype> type_dec_get()
            {
                return type_dec_;
            }

            void type_dec_set(std::shared_ptr<TypePrototype> t)
            {
                type_dec_ = t;
            }

            std::shared_ptr<TypeIdentifierUse>& return_t_get()
            {
                return return_t_;
            }

        protected:
            std::vector<std::shared_ptr<Declaration>> generics_;
            std::vector<VarDec> params_;
            std::shared_ptr<TypeIdentifierUse> return_t_;
            std::shared_ptr<TypePrototype> type_dec_ = nullptr;
    };
}

#endif /* FunctionPrototype */
