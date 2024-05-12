#pragma once
#include "jtoken_behaviour.hpp"
#include "structs/jtoken.hpp"
#include <format>

namespace airashe::json
{
    class jcontainer_behaviour final : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override { delete value->childrens; }

        void assign_value(jtoken_value* target, void const* source) const override
        {
            if (target == source)
                return;

            if (source == nullptr)
            {
                target->childrens = new std::map<jindex, jtoken>();
                return;
            }

            if (target != nullptr)
                delete target->childrens;

            target->childrens = new std::map<jindex, jtoken>();
            const jtoken_value* src = (jtoken_value*)source;
            for (int i = 0; i < src->childrens->size(); i++)
                target->childrens->insert({i, src->childrens->at(i)});
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            assign_value(target, source);
        }

        const char* c_str(jtoken_value const* value) const override
        {
            if (value == nullptr)
                return "";

            return to_string(value).c_str();
        }

        std::string to_string(jtoken_value const* value) const override
        {
            if (value == nullptr)
                return "";

            bool is_array = true;
            const size_t size = value->childrens == nullptr ? 0 : value->childrens->size();
            std::string* properties = new std::string[size];
            std::string* tokens = new std::string[size];

            size_t i = 0;
            for (auto& [key, token] : *value->childrens)
            {
                if (key.get_name() != nullptr)
                {
                    is_array = false;
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

            std::string result = is_array ? "[" : "{";
            for (i = 0; i < size; i++)
            {
                if (!is_array)
                    result += std::format("{0}: {1}", properties[i], tokens[i]);
                else
                    result += std::format("{0}", tokens[i]);
                if (i < size - 1)
                    result += ", ";
            }
            result += is_array ? "]" : "}";
            delete[] properties;
            delete[] tokens;
            return result;
        }

        jtoken& at(jtoken_value* value, const jindex index) const override
        {
            if (value->childrens == nullptr)
                value->childrens = new std::map<jindex, jtoken>();

            for (auto& child : *value->childrens)
                if (child.first == index)
                    return child.second;

            value->childrens->insert({index, jtoken()});
            return value->childrens->at(index);
        }
    };
}
