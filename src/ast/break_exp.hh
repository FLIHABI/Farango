#ifndef BREAK_HH
# define BREAK_HH

# include <memory>

# include "visitor.hh"
# include "loop_exp.hh"
# include "exp.hh"

namespace ast
{
    class BreakExp : public Exp
    {
        public:
            BreakExp()
            {};

            virtual ~BreakExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }

            std::shared_ptr<LoopExp>& loop_get()
            {
                return loop_;
            }

            void loop_set(std::shared_ptr<LoopExp>& loop)
            {
                loop_ = loop;
            }

        private:
            std::shared_ptr<LoopExp> loop_;
    };
}

#endif
