#ifndef TYPE_UNION_HH
# define TYPE_UNION_HH

# include <vector>
# include <memory>
# include <set>

# include "vardec.hh"
# include "type_prototype.hh"
# include "visitor.hh"

namespace ast
{
    class TypeUnion : public TypePrototype
    {
        public:
            TypeUnion(std::shared_ptr<TypeIdentifierDec> type, std::set<std::shared_ptr<TypeIdentifierUse>> unions)
                : TypePrototype(type)
                , unions_(unions)
            {};

            virtual ~TypeUnion()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::set<std::shared_ptr<TypeIdentifierUse>>& unions_get()
            {
                return unions_;
            }

        private:
            std::set<std::shared_ptr<TypeIdentifierUse>> unions_;
    };
}

#endif /* TYPE_UNION_HH */
