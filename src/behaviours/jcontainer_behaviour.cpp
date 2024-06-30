#include "jcontainer_behaviour.hpp"

namespace airashe::json
{
    void jcontainer_behaviour::cleanup(jtoken_value* value) const
    {
        delete value->value.childrens;
        value->modifiers = jmod_none;
        value->value.string = nullptr;
    }

    void jcontainer_behaviour::assign_value(jtoken_value* target, void const* source) const
    {
        if (target == source)
            return;

        if (source == nullptr)
        {
            target->value.childrens = new tokens();
            target->modifiers = jmod_none;
            return;
        }
            
        delete target->value.childrens;

        target->value.childrens = new tokens();
        jtoken_value const* src = (jtoken_value const*)source;
        if (src->value.childrens != nullptr)
        {
            for (auto& [key, token] : *src->value.childrens)
            {
                auto index = jindex(key.get_index(), key.get_name());
                target->value.childrens->insert({ index, token });
            }
        }

        target->modifiers = src->modifiers;
    }

    void jcontainer_behaviour::copy_value(jtoken_value* target, jtoken_value const* source) const
    {
        assign_value(target, source);
    }

    void jcontainer_behaviour::move_value(jtoken_value* target, jtoken_value* source) const
    {
        target->value.childrens = std::move(source->value.childrens);
        target->modifiers = source->modifiers;
        source->value.childrens = nullptr;
        source->modifiers = jmod_none;
    }

    void jcontainer_behaviour::patch_value(jtoken_value* target, jtoken_value const* source,
        jtoken_behaviour const* source_behaviour)
    {
        if (target == nullptr)
            return;
        if (source == nullptr || this == source_behaviour)
        {
            assign_value(target, source);
            return;
        }

        assign_value(target, nullptr);
    }

    std::string jcontainer_behaviour::to_string(jtoken_value const* value) const
    {
        if (value == nullptr)
            return "";

        const size_t size = value->value.childrens == nullptr ? 0 : value->value.childrens->size();
        size_t properties_size = 0;
        std::string* properties = new std::string[size];
        std::string* tokens = new std::string[size];

        size_t i = 0;
        if (size != 0)
            for (auto& [key, token] : *value->value.childrens)
            {
                const auto& key_name = key.get_name();
                if (key_name != nullptr)
                {
                    properties_size++;
                    properties[i] = std::format("\"{0}\"", key_name);
                }

                std::string token_value;
                jtoken_type token_type = token.get_type();
                switch (token_type)
                {
                case jtoken_string:
                    token_value = std::format("\"{0}\"", token.to_string());
                    break;
                case jtoken_null:
                    token_value = "null";
                    break;
                default:
                    token_value = token.to_string();
                    break;
                }
                tokens[i] = token_value;
                i++;
            }

        std::string result;
        result += _start_char;
        bool include_props = properties_size == size;

        for (i = 0; i < size; i++)
        {
            if (include_props)
                result += std::format("{0}: {1}", properties[i], tokens[i]);
            else
                result += std::format("{0}", tokens[i]);
            if (i < size - 1)
                result += ", ";
        }
        result += _end_char;
        delete[] properties;
        delete[] tokens;
        return result;
    }

    jtoken& jcontainer_behaviour::at(jtoken_value* value, const jindex index) const
    {
        if (value->value.childrens == nullptr)
            value->value.childrens = new tokens();

        if (value->value.childrens->contains(index))
            return (*value->value.childrens)[index];

        auto new_index = index.get_index() == -1 ? jindex(value->value.childrens->size(), index.get_name()) : jindex(index);
        value->value.childrens->insert({new_index, jtoken()});
        return (*value->value.childrens)[new_index];
    }

    bool jcontainer_behaviour::empty(jtoken_value const* value) const
    {
        return value->value.childrens->empty();
    }

    size_t jcontainer_behaviour::size(jtoken_value const* value) const
    {
        return value->value.childrens->size();
    }

    jtoken& jcontainer_behaviour::front(jtoken_value* value) const
    {
        if (value->value.childrens == nullptr)
            value->value.childrens = new tokens();

        if (value->value.childrens->empty())
            throw std::out_of_range("jtoken::front");

        return (*value->value.childrens)[0];
    }

    const jtoken& jcontainer_behaviour::front(jtoken_value const* value) const
    {
        return this->front(const_cast<jtoken_value*>(value));
    }

    jtoken& jcontainer_behaviour::back(jtoken_value* value) const
    {
        if (value->value.childrens == nullptr)
            value->value.childrens = new tokens();

        if (value->value.childrens->empty())
            throw std::out_of_range("jtoken::back");

        size_t size = value->value.childrens->size() - 1;
        return (*value->value.childrens)[size];
    }

    const jtoken& jcontainer_behaviour::back(jtoken_value const* value) const
    {
        return this->back(const_cast<jtoken_value*>(value));
    }

    jcontainer_behaviour::iterator jcontainer_behaviour::begin(jtoken_value* value) const
    {
        return value->value.childrens->begin();
    }

    jcontainer_behaviour::iterator jcontainer_behaviour::end(jtoken_value* value) const
    {
        return value->value.childrens->end();
    }
}
