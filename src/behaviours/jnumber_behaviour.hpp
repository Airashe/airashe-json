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
            
            if ((target->modifiers | jmod_number_integer) == target->modifiers)
            {
                target->value.int_number = *(long long int const*)source;
                return;
            }
            
            if ((target->modifiers | jmod_number_float) == target->modifiers)
            {
                target->value.float_number = static_cast<long double>(*(float const*)source);
            }

            if ((target->modifiers | jmod_number_double) == target->modifiers)
            {
                target->value.float_number = static_cast<long double>(*(double const*)source);
            }

            if ((target->modifiers | jmod_number_longdouble) == target->modifiers)
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
            if ((source->modifiers | jmod_number_integer) == source->modifiers)
            {
                target->value.int_number = source->value.int_number;
                return;
            }
            if ((source->modifiers & (jmod_number_float | jmod_number_double | jmod_number_longdouble)) != 0)
            {
                target->value.float_number = source->value.float_number;
            }
        }

        std::string to_string(jtoken_value const* value) const override
        {
            if (value == nullptr)
                return std::to_string(0);
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
            {
                if ((value->modifiers | jmod_number_unsigned) == value->modifiers)
                {
                    unsigned long long int unsigned_value = *(unsigned long long int*)&value->value.int_number;
                    return std::to_string(unsigned_value);
                }
                return std::to_string(value->value.int_number);
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
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
            {
                if ((value->modifiers | jmod_number_unsigned) == value->modifiers)
                {
                    unsigned long long int unsigned_value = *(unsigned long long int*)&value->value.int_number;
                    return static_cast<long long>(unsigned_value);
                }
                return value->value.int_number;
            }
            
            return static_cast<long long>(value->value.float_number);
        }

        unsigned long long to_ull(const jtoken_value* value) const override
        {
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
            {
                if ((value->modifiers | jmod_number_unsigned) == value->modifiers)
                {
                    unsigned long long int unsigned_value = *(unsigned long long int*)&value->value.int_number;
                    return unsigned_value;
                }
                return static_cast<unsigned long long>(value->value.int_number);
            }
            
            return static_cast<unsigned long long>(value->value.float_number);
        }

        long int to_l(const jtoken_value* value) const override
        {
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
                return static_cast<long>(value->value.int_number);
            
            return static_cast<long>(value->value.float_number);
        }
        
        float to_f(const jtoken_value* value) const override
        {
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
                return static_cast<float>(value->value.int_number);
            
            long double max = std::numeric_limits<float>::max();
            long double min = std::numeric_limits<float>::min();
            if (value->value.float_number > max || value->value.float_number < min)
                return 0;
            
            return static_cast<float>(value->value.float_number);
        }
        
        double to_d(const jtoken_value* value) const override
        {
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
                return static_cast<double>(value->value.int_number);

            long double max = std::numeric_limits<float>::max();
            long double min = std::numeric_limits<float>::min();
            if (value->value.float_number > max || value->value.float_number < min)
                return 0;
            
            return static_cast<double>(value->value.float_number);
        }
        
        long double to_ld(const jtoken_value* value) const override
        {
            if ((value->modifiers | jmod_number_integer) == value->modifiers)
                return static_cast<long double>(value->value.int_number);

            return value->value.float_number;
        }
    };
}
