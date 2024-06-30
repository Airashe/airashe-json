#pragma once
#include "jtoken_behaviour.hpp"
#include <format>

#include "structs/jmodifiers.hpp"
#include "structs/jtoken.hpp"
#include "structs/jtoken_value.hpp"

namespace airashe::json
{
    /**
     * @brief Basic behaviour for containers (aka arrays, objects).
     */
    class jcontainer_behaviour : public jtoken_behaviour
    {
    protected:
        /**
         * @brief Start character of container.
         */
        char _start_char;

        /**
         * @brief End character of container.
         */
        char _end_char;

    public:
        typedef typename std::map<jindex, jtoken>::iterator iterator;
        typedef typename std::map<jindex, jtoken>::const_iterator const_iterator;
        typedef typename std::map<jindex, jtoken> tokens;
        
        jcontainer_behaviour() : jtoken_behaviour(), _start_char('{'), _end_char('}') {}
        void cleanup(jtoken_value* value) const override;
        void assign_value(jtoken_value* target, void const* source) const override;
        void copy_value(jtoken_value* target, jtoken_value const* source) const override;
        void move_value(jtoken_value* target, jtoken_value* source) const override;
        void patch_value(jtoken_value* target, jtoken_value const* source, jtoken_behaviour const*  source_behaviour) override;
        
        jtoken& at(jtoken_value* value, const jindex index) const override;
        bool empty(jtoken_value const* value) const override;
        size_t size(jtoken_value const* value) const override;
        jtoken& front(jtoken_value* value) const override;
        const jtoken& front(jtoken_value const* value) const override;
        jtoken& back(jtoken_value* value) const override;
        const jtoken& back(jtoken_value const* value) const override;
        iterator begin(jtoken_value* value) const override;
        const_iterator cbegin(jtoken_value const* value) const override
        {
            return value->value.childrens->begin();
        }
        iterator end(jtoken_value* value) const override;
        const_iterator cend(jtoken_value const* value) const override
        {
            return value->value.childrens->end();
        }

        std::string to_string(jtoken_value const* value) const override;
        long long to_ll(const jtoken_value* value) const override { return 0; }
        unsigned long long to_ull(const jtoken_value* value) const override { return 0; }
        long to_l(const jtoken_value* value) const override { return 0; }
        unsigned long to_ul(const jtoken_value* value) const override { return 0; }
        int to_i(const jtoken_value* value) const override { return 0; }
        unsigned int to_ui(const jtoken_value* value) const override { return 0; }
        short to_s(const jtoken_value* value) const override { return 0; }
        unsigned short to_us(const jtoken_value* value) const override { return 0; }
        char to_c(const jtoken_value* value) const override { return 0; }
        unsigned char to_uc(const jtoken_value* value) const override { return 0; }
        float to_f(const jtoken_value* value) const override { return 0; }
        double to_d(const jtoken_value* value) const override { return 0; }
        long double to_ld(const jtoken_value* value) const override { return 0; }
        bool to_bool(jtoken_value const* value) const override { return false; }
    };
}
