#ifndef CONTINUE_HH
# define CONTINUE_HH

# include <memory>

# include "visitor.hh"
# include "loop_exp.hh"
# include "exp.hh"

namespace ast
{
    class ContinueExp : public Exp
    {
        public:
            ContinueExp()
            {};

            virtual ~ContinueExp()
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

#if 0
            virtual ContinueExp* clone()
            {
                //FIXME, think about loop
                return new ContinueExp();
            }
#endif

        private:
            std::shared_ptr<LoopExp> loop_;
    };
}

#endif
