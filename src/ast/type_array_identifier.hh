#ifndef TYPE_ARRAY_IDENTIFIER_HH
# define TYPE_ARRAY_IDENTIFIER_HH

# include "ast_all.hh"
# include "type_identifier.hh"
# include "type_array.hh"

namespace ast
{
    class TypeArrayIdentifier : public TypeIdentifierUse
    {
        public:
            TypeArrayIdentifier(TypeIdentifier& t)
                : TypeIdentifierUse(t)
            {};

            virtual ~TypeArrayIdentifier()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            unsigned depth_get()
            {
                return depth_;
            }

            void depth_set(unsigned depth)
            {
                depth_ = depth;
            }

            void size_set(std::shared_ptr<Exp>& size)
            {
                size_ = size;
            }

            std::shared_ptr<Exp>& size_get()
            {
                return size_;
            }

            virtual std::shared_ptr<Declaration> dec_get()
            {
                return dec_;
            }

            void set_dec(std::shared_ptr<TypeArray> dec)
            {
                dec_ = dec;
            }

        private:
            unsigned depth_ = 1;
            std::shared_ptr<Exp> size_ = nullptr;
            std::shared_ptr<TypeArray> dec_ = nullptr;
    };
}

#endif /* TYPE_ARRAY_IDENTIFIER_HH */
