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
        protected:
            TypeIdentifier() {}

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

            virtual std::shared_ptr<Id>& type_name_get()
            {
                return type_name_;
            }

            virtual std::vector<std::shared_ptr<T>>& specs_get()
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

    class AutoTypeIdentifier : public TypeIdentifier<Id> {
        using super = TypeIdentifier<Id>;

        public:
            AutoTypeIdentifier() : TypeIdentifier(std::make_shared<Id>(misc::symbol("auto"))) {};
            virtual ~AutoTypeIdentifier() {};

            virtual std::shared_ptr<Id>& type_name_get() override {
                return type_ ? type_->name_get() : super::type_name_get();
            }

            void type_set(std::weak_ptr<Declaration> type) {
                type_ = type.lock();
            }

            virtual std::shared_ptr<Declaration> dec_get() override {
                return type_ ? type_ : super::type_name_get()->dec_get();
            }

        private:
            std::shared_ptr<Declaration> type_;

    };
}

#endif /* TYPE_IDENTIFIER_HH */
