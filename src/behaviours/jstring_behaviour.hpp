#pragma once
#include <cstring>
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
        template<typename T>
        T to_appropriate_integer(const char* str, T (*convert)(const std::string&, size_t*, int)) const
        {
            if (str == nullptr || strlen(str) == 0)
                return 0;

            try
            {
                int base = 10;
                if (str[0] == '0' && str[1] == 'x')
                    base = 16;
                else if (str[0] == '0' && str[1] == 'b')
                    base = 2;
                else if (str[0] == '0')
                    base = 8;
                
                return convert(str, nullptr, base);
            }
            catch (const std::exception&)
            {
                return 0;
            }
        }

        template<typename T>
        T to_appropriate_decimal(const char* str, T (*convert)(const std::string&, size_t*)) const
        {
            if (str == nullptr || strlen(str) == 0)
                return 0;

            try
            {
                return convert(str, nullptr);
            }
            catch (const std::exception&)
            {
                return 0;
            }
        }
    public:
        void cleanup(jtoken_value* value) const override
        {
            delete[] value->value.string;
            value->modifiers = jmod_none;
			value->value.string = nullptr;
        }
        
        void assign_value(jtoken_value* target, void const* source) const override
        {
            const char* src_char = (char const*)source;
            size_t length = strlen(src_char);
            target->value.string = new char[length + 1];
            strcpy(target->value.string, src_char);
            target->modifiers = jmod_none;
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            if (target == source)
				return;

            if (source->value.string == nullptr)
            {
				target->value.string = nullptr;
                target->modifiers = jmod_none;
                return;
            }

            if (target->value.string != nullptr)
                delete[] target->value.string;

			size_t length = strlen(source->value.string);
			target->value.string = new char[length + 1];
			strcpy(target->value.string, source->value.string);
            target->modifiers = source->modifiers;
        }

        std::string to_string(jtoken_value const* value) const override
        {
            return {value->value.string};
        }

        long long int to_ll(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long long int>(value->value.string, std::stoll);
        }

        unsigned long long int to_ull(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long long int>(value->value.string, std::stoull);
        }

        long int to_l(const jtoken_value* value) const override
        {
            return to_appropriate_integer<long int>(value->value.string, std::stol);
        }

        unsigned long int to_ul(const jtoken_value* value) const override
        {
            return to_appropriate_integer<unsigned long int>(value->value.string, std::stoul);
        }
        
        float to_f(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<float>(value->value.string, std::stof);
        }

        double to_d(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<double>(value->value.string, std::stod);
        }

        long double to_ld(const jtoken_value* value) const override
        {
            return to_appropriate_decimal<long double>(value->value.string, std::stold);
        }
    };
}
