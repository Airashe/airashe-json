#include "jstring_behaviour.hpp"

namespace airashe::json
{
    void jstring_behaviour::cleanup(jtoken_value* value) const
    {
        delete[] value->value.string;
        value->modifiers = jmod_none;
        value->value.string = nullptr;
    }

    void jstring_behaviour::assign_value(jtoken_value* target, void const* source) const
    {
        const char* src_char = (char const*)source;
        size_t length = strlen(src_char);
        target->value.string = new char[length + 1];
        strcpy(target->value.string, src_char);
        target->modifiers = jmod_none;
    }

    void jstring_behaviour::copy_value(jtoken_value* target, jtoken_value const* source) const
    {
        if (target == source)
            return;

        if (source->value.string == nullptr)
        {
            target->value.string = nullptr;
            target->modifiers = jmod_none;
            return;
        }
            
        delete[] target->value.string;

        size_t length = strlen(source->value.string);
        target->value.string = new char[length + 1];
        strcpy(target->value.string, source->value.string);
        target->modifiers = source->modifiers;
    }

    void jstring_behaviour::move_value(jtoken_value* target, jtoken_value* source) const
    {
        if (target == source)
            return;

        target->value.string = source->value.string;
        target->modifiers = source->modifiers;
            
        source->value.string = nullptr;
        source->modifiers = jmod_none;
    }

    void jstring_behaviour::patch_value(jtoken_value* target, jtoken_value const* source,
        jtoken_behaviour const* source_behaviour)
    {
        if (target == nullptr)
            return;
            
        if (source_behaviour == this)
            return copy_value(target, source);

        auto _str = source_behaviour->to_string(source);
        assign_value(target, _str.c_str());
    }

    bool jstring_behaviour::empty(jtoken_value const* value) const
    {
        return value->value.string == nullptr || strlen(value->value.string) == 0;
    }

    size_t jstring_behaviour::size(jtoken_value const* value) const
    {
        return strlen(value->value.string);
    }

    std::string jstring_behaviour::to_string(jtoken_value const* value) const
    {
        return {value->value.string};
    }

    bool jstring_behaviour::to_bool(jtoken_value const* value) const
    {
        if (value->value.string == nullptr)
            return false;

        size_t len = strlen(value->value.string);
        if (len == 4)
        {
            if (std::tolower(value->value.string[0]) == 't' &&
                std::tolower(value->value.string[1]) == 'r' &&
                std::tolower(value->value.string[2]) == 'u' &&
                std::tolower(value->value.string[3]) == 'e')
                return true;
            return false;
        }
        if (len == 5)
        {
            if (std::tolower(value->value.string[0]) == 'f' &&
                std::tolower(value->value.string[1]) == 'a' &&
                std::tolower(value->value.string[2]) == 'l' &&
                std::tolower(value->value.string[3]) == 's' &&
                std::tolower(value->value.string[4]) == 'e')
                return false;
        }

        const long long int ll = to_ll(value);
        if (ll == 0)
        {
            const unsigned long long int ull = to_ull(value);
            return ull;
        }
            
        return ll;
    }
}
