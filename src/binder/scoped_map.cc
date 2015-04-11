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

    void ScopedMap::push_dec(ast::Declaration& d_)
    {
        std::shared_ptr<ast::Declaration> d{&d_, [](void *){}};
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
                return;
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
    }

    void ScopedMap::push_dec(ast::TypeUnion& d_)
    {
        std::shared_ptr<ast::TypePrototype> d(&d_, [](void *){});
        push_dec_p_<ast::TypePrototype>(d);
    }

    void ScopedMap::push_dec(ast::TypeStruct& d_)
    {
        std::shared_ptr<ast::TypePrototype> d(&d_, [](void *){});
        push_dec_p_<ast::TypePrototype>(d);
    }

    void ScopedMap::push_dec(ast::FunctionDec& d_)
    {
        std::shared_ptr<ast::FunctionDec> d(&d_, [](void *){});
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
                    return;
                }
                p->type_dec_set(d);
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
        }
    }



    std::shared_ptr<ast::Declaration> ScopedMap::get_s_declaration(misc::symbol s)
    {
        if (map_[s].size() == 0)
            return nullptr;
        return map_[s].top().first;
    }

    unsigned ScopedMap::get_s_age(misc::symbol s)
    {
        if (map_[s].size() == 0)
            return 0;
        return map_[s].top().second;
    }

    unsigned ScopedMap::get_age()
    {
        return age_;
    }
}
