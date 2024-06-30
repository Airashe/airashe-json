#pragma once
#include <string>

#include "jtoken_behaviour.hpp"
#include "structs/jmodifiers.hpp"
#include "structs/jtoken_value.hpp"

namespace airashe::json
{
    class jboolean_behaviour : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override;
        void assign_value(jtoken_value* target, const void* source) const override;
        void copy_value(jtoken_value* target, const jtoken_value* source) const override;
        void move_value(jtoken_value* target, jtoken_value* source) const override;
        void patch_value(jtoken_value* target, jtoken_value const* source, jtoken_behaviour const* source_behaviour) override;
        long long to_ll(const jtoken_value* value) const override { return value->value.boolean; }
        unsigned long long to_ull(const jtoken_value* value) const override { return value->value.boolean; }
        long to_l(const jtoken_value* value) const override { return value->value.boolean; }
        unsigned long to_ul(const jtoken_value* value) const override { return value->value.boolean; }
        int to_i(const jtoken_value* value) const override { return value->value.boolean; }
        unsigned to_ui(const jtoken_value* value) const override { return value->value.boolean; }
        short to_s(const jtoken_value* value) const override { return value->value.boolean; }
        unsigned short to_us(const jtoken_value* value) const override { return value->value.boolean; }
        char to_c(const jtoken_value* value) const override { return value->value.boolean; }
        unsigned char to_uc(const jtoken_value* value) const override { return value->value.boolean; }
        float to_f(const jtoken_value* value) const override { return value->value.boolean; }
        double to_d(const jtoken_value* value) const override { return value->value.boolean; }
        long double to_ld(const jtoken_value* value) const override { return value->value.boolean; }
        bool to_bool(jtoken_value const* value) const override { return value->value.boolean; }
        std::string to_string(jtoken_value const* value) const override
        {
            if (value == nullptr || !value->value.boolean)
                return "false";
            return "true";
        }
    };
}
