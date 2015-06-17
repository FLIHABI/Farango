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

#if 0
    ExpList* ExpList::clone()
    {
        ExpList* ptr = new ExpList();
        for (auto p : list_)
            ptr->list_.emplace_back(p->clone());
        return ptr;
    }

    ExpListInner* ExpListInner::clone()
    {
        ExpListInner* ptr = new ExpListInner();
        for (auto p : list_)
            ptr->list_.emplace_back(p->clone());
        return ptr;
    }

    ExpListFunction* ExpListFunction::clone()
    {
        ExpListFunction* ptr = new ExpListFunction();
        for (auto p : list_)
            ptr->list_.emplace_back(p->clone());
        return ptr;
    }
#endif
}
