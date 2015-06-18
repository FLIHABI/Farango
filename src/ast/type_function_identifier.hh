#ifndef TYPE_FUNCTION_IDENTIFIER
# define TYPE_FUNCTION_IDENTIFIER

# include "ast_all.hh"
# include "type_identifier.hh"

namespace ast
{
    class TypeFunctionIdentifier : public TypeIdentifierUse
    {
        public:
            TypeFunctionIdentifier(std::vector<std::shared_ptr<TypeIdentifierUse>> params,
                                   std::shared_ptr<TypeIdentifierUse> return_t)
                : TypeIdentifierUse(std::make_shared<Id>(""))
                , params_(params)
                , return_t_(return_t)
            {};

            virtual ~TypeFunctionIdentifier()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::vector<std::shared_ptr<TypeIdentifierUse>>& params_get()
            {
                return params_;
            }

            std::shared_ptr<TypeIdentifierUse>& return_t_get()
            {
                return return_t_;
            }

        protected:
            std::vector<std::shared_ptr<TypeIdentifierUse>> params_;
            std::shared_ptr<TypeIdentifierUse> return_t_;
    };
}
#endif /* TYPE_FUNCTION_IDENTIFIER */
