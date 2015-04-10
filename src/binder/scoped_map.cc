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

    void ScopedMap::push_dec(std::shared_ptr<ast::Declaration> d)
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

    void ScopedMap::push_dec(std::shared_ptr<ast::TypeUnion> d)
    {
        push_dec_p_<ast::TypePrototype>(d);
    }

    void ScopedMap::push_dec(std::shared_ptr<ast::TypeStruct> d)
    {
        push_dec_p_<ast::TypePrototype>(d);
    }

    void ScopedMap::push_dec(std::shared_ptr<ast::FunctionDec> d)
    {
        push_dec_p_<ast::FunctionPrototype>(d);
    }

    template <typename T>
    void ScopedMap::push_dec_p_(std::shared_ptr<T> d)
    {
        misc::symbol s = d->name_get()->s_get();
        d->type_dec_set(d);
        if (map_[s].size() == 0)
        {
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
        else
        {
            unsigned old_ = map_[s].top().second;
            if (old_ == age_)
            {
                std::shared_ptr<T> p =
                    std::dynamic_pointer_cast<T>(map_[s].top().first);
                if (p == nullptr || p->type_dec_get() != nullptr)
                {
                    //FIXME ERROR: var already def;
                }
                p->type_dec_set(d);
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
    }
}
