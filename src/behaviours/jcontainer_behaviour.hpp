#pragma once
#include "jtoken_behaviour.hpp"
#include "structs/jtoken.hpp"
#include <format>

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
        jcontainer_behaviour() : jtoken_behaviour(), _start_char('{'), _end_char('}') { }
        
        void cleanup(jtoken_value* value) const override
        {
            delete value->value.childrens;
            value->modifiers = jmod_none;
            value->value.string = nullptr;
        }

        void assign_value(jtoken_value* target, void const* source) const override
        {
            if (target == source)
                return;

            if (source == nullptr)
            {
                target->value.childrens = new std::map<jindex, jtoken>();
                target->modifiers = jmod_none;
                return;
            }

            if (target != nullptr)
                delete target->value.childrens;

            target->value.childrens = new std::map<jindex, jtoken>();
            jtoken_value const* src = (jtoken_value const*)source;
            for (int i = 0; i < src->value.childrens->size(); i++)
                target->value.childrens->insert({i, src->value.childrens->at(i)});

            target->modifiers = src->modifiers;
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            assign_value(target, source);
        }

        std::string to_string(jtoken_value const* value) const override
        {
            if (value == nullptr)
                return "";
            
            const size_t size = value->value.childrens == nullptr ? 0 : value->value.childrens->size();
            size_t properties_size = 0;
            std::string* properties = new std::string[size];
            std::string* tokens = new std::string[size];

            size_t i = 0;
            if (size != 0)
                for (auto& [key, token] : *value->value.childrens)
            {
                if (key.get_name() != nullptr)
                {
                    properties_size++;
                    properties[i] = std::format("\"{0}\"", key.get_name());
                }

                std::string token_value;
                if (token.get_type() == jtoken_string)
                    token_value = std::format("\"{0}\"", token.to_string());
                else
                    token_value = token.to_string();
                tokens[i] = token_value;
                i++;
            }

            std::string result;
            result += _start_char;
            bool include_props = properties_size == size;
            
            for (i = 0; i < size; i++)
            {
                if (include_props)
                    result += std::format("{0}: {1}", properties[i], tokens[i]);
                else
                    result += std::format("{0}", tokens[i]);
                if (i < size - 1)
                    result += ", ";
            }
            result += _end_char;
            delete[] properties;
            delete[] tokens;
            return result;
        }

        jtoken& at(jtoken_value* value, const jindex index) const override
        {
            if (value->value.childrens == nullptr)
                value->value.childrens = new std::map<jindex, jtoken>();

            for (auto& child : *value->value.childrens)
                if (child.first == index)
                    return child.second;

            value->value.childrens->insert({index, jtoken()});
            return value->value.childrens->at(index);
        }

        long long to_ll(const jtoken_value* value) const override { return 0; }

        unsigned long long to_ull(const jtoken_value* value) const override { return 0; }

        float to_f(const jtoken_value* value) const override { return 0; }

        double to_d(const jtoken_value* value) const override { return 0; }

        long double to_ld(const jtoken_value* value) const override { return 0; }
    };
}
