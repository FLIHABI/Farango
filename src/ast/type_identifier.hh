#ifndef TYPE_IDENTIFIER_HH
# define TYPE_IDENTIFIER_HH

# include <vector>
# include <memory>

# include "ast.hh"
# include "id.hh"
# include "declaration.hh"
# include "visitor.hh"

namespace ast
{
    template <typename T>
    class TypeIdentifier : public Exp
    {
        public:
            TypeIdentifier(std::shared_ptr<Id> type_name, std::vector<std::shared_ptr<T>> specs)
                : type_name_(type_name)
                , specs_(specs)
            {};

            TypeIdentifier(std::shared_ptr<Id> type_name)
                : type_name_(type_name)
            {};

            virtual ~TypeIdentifier()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<Id>& type_name_get()
            {
                return type_name_;
            }

            std::vector<std::shared_ptr<T>>& specs_get()
            {
                return specs_;
            }

            virtual std::shared_ptr<Declaration> dec_get()
            {
                return type_name_->dec_get();
            }

        private:
            std::shared_ptr<Id> type_name_;
            std::vector<std::shared_ptr<T>> specs_;

    };
}

#endif /* TYPE_IDENTIFIER_HH */
