# include "iostream"
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
            auto d = map_.find(history_.top())->second.top().first;

            {
                std::shared_ptr<ast::TypePrototype> def =
                    std::dynamic_pointer_cast<ast::TypePrototype>(d);
                if (def && def->type_dec_get() == nullptr)
                {
                    e_ << misc::error::error_type::bind ;
                    e_ << def->name_get()->s_get().name_get() << " has no definition" << std::endl;
                }
            }

            {
                std::shared_ptr<ast::FunctionPrototype> def =
                    std::dynamic_pointer_cast<ast::FunctionPrototype>(d);
                if (def && def->type_dec_get() == nullptr)
                {
                    e_ << misc::error::error_type::bind ;
                    e_ << def->name_get()->s_get().name_get() << " has no definition" << std::endl;
                }
            }

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
            history_.push(s);
        }
        else
        {
            unsigned old_ = map_[s].top().second;
            if (old_ == age_)
            {
                e_ << misc::error::error_type::bind;
                e_ << s << " is already defined in this scop" << std::endl;
                return;
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
            history_.push(s);
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
            history_.push(s);
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
                    e_ << misc::error::error_type::bind;
                    e_ << s << " is already defined in this scop" << std::endl;
                    return;
                }
                p->type_dec_set(d);
            }
            map_[s].push(std::pair<std::shared_ptr<ast::Declaration>, unsigned>(d, age_));
            history_.push(s);
        }
    }

    std::shared_ptr<ast::Declaration> ScopedMap::get_s_declaration(misc::symbol s)
    {
        if (map_[s].size() == 0)
        {
            e_ << misc::error::error_type::bind;
            e_ << s << " never defined in this scop" << std::endl;
            return nullptr;
        }
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
