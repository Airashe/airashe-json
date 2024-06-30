#include "jnumber_behaviour.hpp"

namespace airashe::json
{
    void jnumber_behaviour::cleanup(jtoken_value* value) const
    {
        value->modifiers = jmod_none;
        value->value.string = nullptr;
    }

    void jnumber_behaviour::assign_value(jtoken_value* target, const void* source) const
    {
        if (source == nullptr)
        {
            target->modifiers = jmod_number_integer;
            target->value.int_number = 0;
            return;
        }

        if (is_integer(target))
        {
            if (has_flag(target, jmod_number_char))
            {
                target->value.int_number = *(char const*)source;
                if (has_flag(target, jmod_number_unsigned))
                {
                    target->value.int_number = *(unsigned char const*)source;
                }
            }
            if (has_flag(target, jmod_number_short))
            {
                target->value.int_number = *(short const*)source;
                if (has_flag(target, jmod_number_unsigned))
                {
                    target->value.int_number = *(unsigned short const*)source;
                }
            }
            if (has_flag(target, jmod_number_integer))
            {
                target->value.int_number = *(int const*)source;
                if (has_flag(target, jmod_number_unsigned))
                {
                    target->value.int_number = *(unsigned int const*)source;
                }
            }
            if (has_flag(target, jmod_number_long))
            {
                target->value.int_number = *(long const*)source;
                if (has_flag(target, jmod_number_unsigned))
                {
                    target->value.int_number = *(unsigned long const*)source;
                }
            }
            if (has_flag(target, jmod_number_long_long))
            {
                target->value.int_number = *(long long const*)source;
                if (has_flag(target, jmod_number_unsigned))
                {
                    target->value.int_number = *(unsigned long long const*)source;
                }
            }

            return;
        }
            
        if (has_flag(target, jmod_number_float))
        {
            target->value.float_number = static_cast<long double>(*(float const*)source);
        }

        if (has_flag(target, jmod_number_double))
        {
            target->value.float_number = static_cast<long double>(*(double const*)source);
        }

        if (has_flag(target, jmod_number_longdouble))
        {
            target->value.float_number = *(long double const*)source;
        }
    }

    void jnumber_behaviour::copy_value(jtoken_value* target, const jtoken_value* source) const
    {
        if (source == nullptr)
        {
            target->modifiers = jmod_number_integer;
            target->value.int_number = 0;
            return;
        }
            
        target->modifiers = source->modifiers;
        if (is_integer(source))
        {
            target->value.int_number = source->value.int_number;
            return;
        }
            
        if (is_decimal(source))
        {
            target->value.float_number = source->value.float_number;
        }
    }

    void jnumber_behaviour::move_value(jtoken_value* target, jtoken_value* source) const
    {
        if (target == nullptr)
            return;
            
        if (source == nullptr)
        {
            target->modifiers = jmod_number_integer;
            target->value.int_number = 0;
            return;
        }

        target->modifiers = source->modifiers;
        if (is_integer(source))
        {
            target->value.int_number = source->value.int_number;
            return;
        }
            
        if (is_decimal(source))
        {
            target->value.float_number = source->value.float_number;
        }

        source->modifiers = jmod_none;
        source->value.string = nullptr;
    }

    void jnumber_behaviour::patch_value(jtoken_value* target, jtoken_value const* source,
        jtoken_behaviour const* source_behaviour)
    {
        if (target == nullptr)
            return;
            
        if (source == nullptr)
        {
            target->modifiers = jmod_number_integer;
            target->value.int_number = 0;
            return;
        }

        if (source_behaviour == this)
        {
            copy_value(target, source);
            return;
        }

        if (has_flag(target, jmod_number_char))
        {
            if (has_flag(target, jmod_number_unsigned))
            {
                unsigned char v = source_behaviour->to_uc(source);
                assign_value(target, &v);
            }
            else
            {
                char v = source_behaviour->to_c(source);
                assign_value(target, &v);
            }
        }
        else if (has_flag(target, jmod_number_short))
        {
            if (has_flag(target, jmod_number_unsigned))
            {
                unsigned short v = source_behaviour->to_us(source);
                assign_value(target, &v);
            }
            else
            {
                short v = source_behaviour->to_s(source);
                assign_value(target, &v);
            }
        }
        else if (has_flag(target, jmod_number_integer))
        {
            if (has_flag(target, jmod_number_unsigned))
            {
                unsigned int v = source_behaviour->to_ui(source);
                assign_value(target, &v);
            }
            else
            {
                int v = source_behaviour->to_i(source);
                assign_value(target, &v);
            }
        }
        else if (has_flag(target, jmod_number_long))
        {
            if (has_flag(target, jmod_number_unsigned))
            {
                unsigned long v = source_behaviour->to_ul(source);
                assign_value(target, &v);
            }
            else
            {
                long v = source_behaviour->to_l(source);
                assign_value(target, &v);
            }
        }
        else if (has_flag(target, jmod_number_long_long))
        {
            if (has_flag(target, jmod_number_unsigned))
            {
                unsigned long long v = source_behaviour->to_ull(source);
                assign_value(target, &v);
            }
            else
            {
                long long v = source_behaviour->to_ll(source);
                assign_value(target, &v);
            }
        }
        else if (has_flag(target, jmod_number_float))
        {
            float v = source_behaviour->to_f(source);
            assign_value(target, &v);
        }
        else if (has_flag(target, jmod_number_double))
        {
            double v = source_behaviour->to_d(source);
            assign_value(target, &v);
        }
        else if (has_flag(target, jmod_number_longdouble))
        {
            long double v = source_behaviour->to_ld(source);
            assign_value(target, &v);
        }
        else
        {
            target->modifiers = jmod_number_integer;
            target->value.int_number = 0;
            return;
        }
    }

    std::string jnumber_behaviour::to_string(jtoken_value const* value) const
    {
        if (value == nullptr)
            return std::to_string(0);
        if (is_integer(value))
        {
            if (has_flag(value, jmod_number_unsigned))
            {
                if (has_flag(value, jmod_number_integer))
                    return std::to_string(*(unsigned int*)&value->value.int_number);
                if(has_flag(value, jmod_number_char))
                    return std::to_string(*(unsigned char*)&value->value.int_number);
                if (has_flag(value, jmod_number_short))
                    return std::to_string(*(unsigned short*)&value->value.int_number);
                if (has_flag(value, jmod_number_long))
                    return std::to_string(*(unsigned long*)&value->value.int_number);
                if (has_flag(value, jmod_number_long_long))
                    return std::to_string(*(unsigned long long*)&value->value.int_number);
            }
            if (has_flag(value, jmod_number_integer))
                return std::to_string(*(int*)&value->value.int_number);
            if(has_flag(value, jmod_number_char))
                return std::to_string(*(char*)&value->value.int_number);
            if (has_flag(value, jmod_number_short))
                return std::to_string(*(short*)&value->value.int_number);
            if (has_flag(value, jmod_number_long))
                return std::to_string(*(long*)&value->value.int_number);
            if (has_flag(value, jmod_number_long_long))
                return std::to_string(*(long long*)&value->value.int_number);
        }

        auto value_str = std::to_string(value->value.float_number);
        if (value_str.find('.') != std::string::npos)
        {
            value_str = value_str.substr(0, value_str.find_last_not_of('0')+1);
            if (value_str.find('.') == value_str.size() - 1)
                value_str = value_str.substr(0, value_str.size() - 1);
        }
        return value_str;
    }

    bool jnumber_behaviour::to_bool(jtoken_value const* value) const
    {
        if (is_integer(value))
        {
            if(has_flag(value, jmod_number_unsigned))
                return static_cast<bool>(to_appropriate_integer<unsigned long long int>(value));
            auto test = (to_appropriate_integer<long long int>(value));
            return static_cast<bool>(test);
        }
        if (is_decimal(value))
            return static_cast<bool>(to_appropriate_integer<long double>(value)) != 0;
        return false;
    }
}
