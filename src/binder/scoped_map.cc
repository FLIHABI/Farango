# include "scoped_map.hh"

namespace binder
{
    void ScopedMap::start_scop()
    {
        age_++;
        history_.push("__context");
    }

    void ScopedMap::end_scop()
    {
        age_--;
        while (history_.top() != "__context")
        {
            map_.find(history_.top())->second.pop();
            history_.pop();
        }
        history_.pop();
    }

    void ScopedMap::push_dec(std::shared_ptr<ast::VarDec> d)
    {
        misc::symbol s = d->name_get()->s_get();
        if (map_[s].size() == 0)
        {
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
        else
        {
            unsigned old_ = map_[s].top().second;
            if (old_ == age_)
            {
                //FIXME ERROR: var already def;
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
    }
}
