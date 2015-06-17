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

#if 0
            virtual ExpList* clone();
#endif
            std::vector<std::shared_ptr<Exp>>& list_get();

        protected:
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

#if 0
            virtual ExpListInner* clone();
#endif
    };

    class ExpListFunction : public ExpList
    {
        public:
            ExpListFunction()
            {};

            ExpListFunction(ExpList& e)
                 : ExpList(e)
            {};
            virtual ~ExpListFunction()
            {};
            void virtual accept(Visitor& v)
            {
                v(*this);
            }

#if 0
            virtual ExpListFunction* clone();
#endif
    };
}

#endif /* EXP_LIST_HH */
