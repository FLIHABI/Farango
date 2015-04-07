#ifndef TYPE_UNION_HH
# define TYPE_UNION_HH

# include <vector>

# include "vardec.hh"
# include "type_prototype.hh"
# include "visitor.hh"

namespace ast
{
    class TypeUnion : public TypePrototype
    {
        public:
            TypeUnion(std::shared_ptr<TypeIdentifier> type, std::vector<TypeIdentifier> unions)
                : TypePrototype(type)
                , unions_(unions)
            {};

            virtual ~TypeUnion()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::vector<TypeIdentifier>& unions_get()
            {
                return unions_;
            }

        private:
            std::vector<TypeIdentifier> unions_;
    };
}

#endif /* TYPE_UNION_HH */
