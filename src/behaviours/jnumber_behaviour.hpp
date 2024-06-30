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
        void cleanup(jtoken_value* value) const override;
        void assign_value(jtoken_value* target, const void* source) const override;
        void copy_value(jtoken_value* target, const jtoken_value* source) const override;
        void move_value(jtoken_value* target, jtoken_value* source) const override;
        void patch_value(jtoken_value* target, jtoken_value const* source, jtoken_behaviour const* source_behaviour) override;

        std::string to_string(jtoken_value const* value) const override;
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
        bool to_bool(jtoken_value const* value) const override;
    };
}
