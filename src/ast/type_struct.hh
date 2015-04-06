#ifndef TYPE_STRUCT_HH
# define TYPE_STRUCT_HH

# include <vector>

# include "vardec.hh"
# include "type_prototype.hh"

namespace ast
{
    class TypeStruct : public TypePrototype
    {
        public:
            TypeStruct(std::shared_ptr<TypeIdentifier> type, std::vector<VarDec> members)
                : TypePrototype(type)
                , members_(members)
            {};

            virtual ~TypeStruct()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::vector<VarDec>& members_get()
            {
                return members_;
            }

        private:
            std::vector<VarDec> members_;
    };
}

#endif /* TYPE_STRUCT_HH */
