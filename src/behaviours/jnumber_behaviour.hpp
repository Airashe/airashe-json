#pragma once
#include <string>

#include "jtoken_behaviour.hpp"
#include "structs/jmodifiers.hpp"
#include "structs/jtoken_value.hpp"

namespace airashe::json
{
    /**
     * Behaviour for tokens that contains any kind of number.
     */
    class jnumber_behaviour final : public jtoken_behaviour
    {
    private:
        bool is_integer(const jtoken_value* value) const
        {
            return in_mask(value, jmod_number_integer | jmod_number_long | jmod_number_long_long | jmod_number_char | jmod_number_short);
        }
        bool is_decimal(const jtoken_value* value) const
        {
            return in_mask(value, jmod_number_float | jmod_number_double | jmod_number_longdouble);
        }
        
        template<typename T>
        T to_appropriate_integer(const jtoken_value* value) const
        {
            if (is_integer(value))
                return static_cast<T>(value->value.int_number);
            return static_cast<T>(value->value.float_number);
        }
    public:
        void cleanup(jtoken_value* value) const override
        {
            value->modifiers = jmod_none;
            value->value.string = nullptr;
        }

        void assign_value(jtoken_value* target, const void* source) const override
        {
            if (source == nullptr)
            {
                target->modifiers = jmod_number_integer;
                target->value.int_number = 0;
                return;
            }

            if (is_integer(target))
            {
                target->value.int_number = *(long long int const*)source;
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

        void copy_value(jtoken_value* target, const jtoken_value* source) const override
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

        std::string to_string(jtoken_value const* value) const override
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

        long long to_ll(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long long>(value);
        }

        unsigned long long to_ull(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long long>(value);
        }

        long int to_l(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long int>(value);
        }

        unsigned long to_ul(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long int>(value);
        }

        int to_i(const jtoken_value* value) const override
        {
            return to_appropriate_integer<int>(value);
        }

        unsigned int to_ui(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned int>(value);
        }

        
        short int to_s(const jtoken_value* value) const override
        {
            return to_appropriate_integer<short int>(value);
        }
        
        unsigned short int to_us(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned short int>(value);
        }
        
        char to_c(const jtoken_value* value) const override
        {
            return to_appropriate_integer<char>(value);
        }

        unsigned char to_uc(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned char>(value);
        }
        
        float to_f(const jtoken_value* value) const override
        {
            return to_appropriate_integer<float>(value);
        }
        
        double to_d(const jtoken_value* value) const override
        {
            return to_appropriate_integer<double>(value);
        }
        
        long double to_ld(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long double>(value);
        }
    };
}
