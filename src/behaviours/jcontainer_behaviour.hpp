#pragma once
#include "jtoken_behaviour.hpp"
#include "structs/jtoken.hpp"
#include <format>

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
            jtoken_value const* src = (jtoken_value const*)source;
            for (int i = 0; i < src->childrens->size(); i++)
                target->childrens->insert({i, src->childrens->at(i)});
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            assign_value(target, source);
        }

        std::string to_string(jtoken_value const* value) const override
        {
            if (value == nullptr)
                return "";
            
            const size_t size = value->childrens == nullptr ? 0 : value->childrens->size();
            size_t properties_size = 0;
            std::string* properties = new std::string[size];
            std::string* tokens = new std::string[size];

            size_t i = 0;
            if (size != 0)
                for (auto& [key, token] : *value->childrens)
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
