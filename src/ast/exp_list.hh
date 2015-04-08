#ifndef EXP_LIST_HH
# define EXP_LIST_HH

# include <vector>
# include <memory>

# include "ast_all.hh"
# include "value.hh"
# include "visitor.hh"

namespace ast
{
    class ExpList : public Value
    {
        public:
            ExpList()
            {};
            virtual ~ExpList()
            {};

            void virtual accept(Visitor& v);

            void push(std::shared_ptr<Exp> e);
            std::vector<std::shared_ptr<Exp>>& list_get();

        private:
            std::vector<std::shared_ptr<Exp>> list_;
    };

    class ExpListInner : public ExpList
    {
        public:
            ExpListInner()
            {};

            ExpListInner(ExpList& e)
                 : ExpList(e)
            {};
            virtual ~ExpListInner()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }
    };

    class ExpListFunction : public ExpList
    {
        public:
            ExpListFunction()
            {};
            virtual ~ExpListFunction()
            {};
            void virtual accept(Visitor& v)
            {
                v(*this);
            }
    };
}

#endif /* EXP_LIST_HH */
