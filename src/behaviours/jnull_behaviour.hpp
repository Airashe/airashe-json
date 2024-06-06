#pragma once
#include <string>

#include "jtoken_behaviour.hpp"
#include "structs/jmodifiers.hpp"
#include "structs/jtoken_value.hpp"

namespace airashe::json
{
    class jnull_behaviour : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override
        {
            value->modifiers = jmod_none;
            value->value.string = nullptr;
        }
        
        void assign_value(jtoken_value* target, const void* source) const override
        {
            target->modifiers = jmod_none;
            target->value.string = nullptr;
        }
        
        void copy_value(jtoken_value* target, const jtoken_value* source) const override
        {
            target->modifiers = jmod_none;
            target->value.string = nullptr;
        }
        
        long long to_ll(const jtoken_value* value) const override { return 0; }
        
        unsigned long long to_ull(const jtoken_value* value) const override { return 0; }
        long to_l(const jtoken_value* value) const override { return 0; }
        unsigned long to_ul(const jtoken_value* value) const override { return 0; }
        int to_i(const jtoken_value* value) const override { return 0; }
        unsigned to_ui(const jtoken_value* value) const override { return 0; }
        short to_s(const jtoken_value* value) const override { return 0; }
        unsigned short to_us(const jtoken_value* value) const override { return 0; }
        char to_c(const jtoken_value* value) const override { return 0; }
        unsigned char to_uc(const jtoken_value* value) const override { return 0; }
        float to_f(const jtoken_value* value) const override { return 0; }
        double to_d(const jtoken_value* value) const override { return 0; }
        long double to_ld(const jtoken_value* value) const override { return 0; }
        bool to_bool(jtoken_value const* value) const override { return 0; }
        std::string to_string(jtoken_value const* value) const override { return ""; }
    };
}
