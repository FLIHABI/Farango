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

            void type_name_set(std::shared_ptr<Id>& id)
            {
                type_name_ = id;
            }

            virtual std::vector<std::shared_ptr<T>>& specs_get()
            {
                return specs_;
            }

            virtual std::shared_ptr<Declaration> dec_get()
            {
                return type_name_->dec_get();
            }

            void set_checked(bool check)
            {
                is_checked_ = check;
            }

            bool is_checked()
            {
                return is_checked_;
            }

        protected:
            std::shared_ptr<Id> type_name_;
            std::vector<std::shared_ptr<T>> specs_;
            bool is_checked_ = false;
    };

    class TypeIdentifierUse : public TypeIdentifier<TypeIdentifierUse>
    {
        public:
            TypeIdentifierUse(std::shared_ptr<Id> type_name, std::vector<std::shared_ptr<TypeIdentifierUse>> specs)
                :TypeIdentifier(type_name, specs)
            {};

            TypeIdentifierUse(std::shared_ptr<Id> type_name)
                : TypeIdentifier(type_name)
            {};

            virtual ~TypeIdentifierUse()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

    };

    class AutoTypeIdentifier : public TypeIdentifierUse {
        using super = TypeIdentifierUse;

        public:
            AutoTypeIdentifier() : TypeIdentifierUse(std::make_shared<Id>(misc::symbol("auto"))) {};
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
