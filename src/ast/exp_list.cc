#include "exp_list.hh"

namespace ast
{
    void ExpList::accept(Visitor& v)
    {
        v(*this);
    }

    void ExpList::push(std::shared_ptr<Exp> e)
    {
        list_.push_back(e);
    }

    std::vector<std::shared_ptr<Exp>>& ExpList::list_get()
    {
        return list_;
    }
}
