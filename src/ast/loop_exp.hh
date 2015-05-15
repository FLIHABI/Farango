#ifndef LOOP_EXP_HH
# define LOOP_EXP_HH

# include "visitor.hh"
# include "exp.hh"

namespace ast
{
    class LoopExp : public Exp
    {
        public:
            virtual ~LoopExp()
            {};

            void virtual accept(Visitor& v)
            {
                v(*this);
            }
    };
}
#endif /* LOOP_EXP_HH */
