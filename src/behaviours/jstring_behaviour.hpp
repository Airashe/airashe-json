#pragma once
#include <cstring>
#include <string>
#include <functional>

#include "structs/jtoken_value.hpp"
#include "jtoken_behaviour.hpp"

namespace airashe::json
{
    /**
     * @brief Behaviour for string tokens.
     */
    class jstring_behaviour final : public jtoken_behaviour
    {
    private:
        template <typename T>
        T to_appropriate_integer(const char* str) const
        {
            if (str == nullptr || strlen(str) == 0)
                return 0;

            int base = 10;
            if (str[0] == '0' && str[1] == 'x')
                base = 16;
            else if (str[0] == '0' && str[1] == 'b')
                base = 2;
            else if (str[0] == '0')
                base = 8;
            try
            {
                if (std::is_signed_v<T>)
                {
                    try
                    {
                        long long int up_val = std::stoll(str, nullptr, base);
                        return static_cast<T>(up_val);
                    }
                    catch (const std::exception&)
                    {
                        unsigned long long int p_val = std::stoull(str, nullptr, base);
                        return static_cast<T>(p_val);
                    }
                }
                else
                {
                    unsigned long long int p_val = std::stoull(str, nullptr, base);
                    return static_cast<T>(p_val);
                }
            }
            catch (const std::exception&)
            {
                return 0;
            }
        }

        template <typename T>
        T to_appropriate_decimal(const char* str) const
        {
            if (str == nullptr || strlen(str) == 0)
                return 0;

            try
            {
                return static_cast<T>(std::stold(str, nullptr));
            }
            catch (const std::exception&)
            {
                return 0;
            }
        }

        template <typename T>
        T to_appropriate_char(const char* str) const
        {
            if (str == nullptr)
                return 0;

            const size_t size = strlen(str);
            if (size != 1)
                return 0;

            return static_cast<T>(str[0]);
        }

    public:
        void cleanup(jtoken_value* value) const override;
        void assign_value(jtoken_value* target, void const* source) const override;
        void copy_value(jtoken_value* target, jtoken_value const* source) const override;
        void move_value(jtoken_value* target, jtoken_value* source) const override;
        void patch_value(jtoken_value* target, jtoken_value const* source, jtoken_behaviour const* source_behaviour) override;

        bool empty(jtoken_value const* value) const override;
        size_t size(jtoken_value const* value) const override;
        
        std::string to_string(jtoken_value const* value) const override;
        long long int to_ll(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long long int>(value->value.string);
        }
        unsigned long long int to_ull(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long long int>(value->value.string);
        }
        long int to_l(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long int>(value->value.string);
        }
        unsigned long int to_ul(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long int>(value->value.string);
        }
        int to_i(const jtoken_value* value) const override
        {
            return to_appropriate_integer<int>(value->value.string);
        }
        unsigned int to_ui(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned int>(value->value.string);
        }
        short to_s(const jtoken_value* value) const override
        {
            return to_appropriate_integer<short>(value->value.string);
        }
        unsigned short to_us(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned short>(value->value.string);
        }
        char to_c(const jtoken_value* value) const override
        {
            if (strlen(value->value.string) == 1)
                return to_appropriate_char<char>(value->value.string);
            
            return to_appropriate_integer<char>(value->value.string);
        }
        unsigned char to_uc(const jtoken_value* value) const override
        {
            if (strlen(value->value.string) == 1)
                return to_appropriate_char<unsigned char>(value->value.string);
            
            return to_appropriate_integer<unsigned char>(value->value.string);
        }
        float to_f(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<float>(value->value.string);
        }
        double to_d(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<double>(value->value.string);
        }
        long double to_ld(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<long double>(value->value.string);
        }
        bool to_bool(jtoken_value const* value) const override;
    };
}
