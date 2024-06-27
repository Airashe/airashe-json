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
        
        jcontainer_behaviour() : jtoken_behaviour(), _start_char('{'), _end_char('}')
        {
        }

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
                target->value.childrens = new tokens();
                target->modifiers = jmod_none;
                return;
            }
            
            delete target->value.childrens;

            target->value.childrens = new tokens();
            jtoken_value const* src = (jtoken_value const*)source;
            if (src->value.childrens != nullptr)
            {
                for (auto& [key, token] : *src->value.childrens)
                {
                    auto index = jindex(key.get_index(), key.get_name());
					target->value.childrens->insert({ index, token });
                }
            }

            target->modifiers = src->modifiers;
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            assign_value(target, source);
        }

        void move_value(jtoken_value* target, jtoken_value* source) const override
        {
            target->value.childrens = std::move(source->value.childrens);
            target->modifiers = source->modifiers;
            source->value.childrens = nullptr;
            source->modifiers = jmod_none;
        }

        void patch_value(jtoken_value* target, jtoken_value const* source, jtoken_behaviour* const source_behaviour) override
        {
            if (target == nullptr)
                return;
            if (source == nullptr || this == source_behaviour)
            {
                assign_value(target, source);
                return;
            }

            assign_value(target, nullptr);
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
                    const auto& key_name = key.get_name();
                    if (key_name != nullptr)
                    {
                        properties_size++;
                        properties[i] = std::format("\"{0}\"", key_name);
                    }

                    std::string token_value;
                    jtoken_type token_type = token.get_type();
                    switch (token_type)
                    {
                    case jtoken_string:
                        token_value = std::format("\"{0}\"", token.to_string());
                        break;
                    case jtoken_null:
                        token_value = "null";
                        break;
                    default:
                        token_value = token.to_string();
                        break;
                    }
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
                value->value.childrens = new tokens();

            if (value->value.childrens->contains(index))
                return (*value->value.childrens)[index];

            auto new_index = index.get_index() == -1 ? jindex(value->value.childrens->size(), index.get_name()) : jindex(index);
            value->value.childrens->insert({new_index, jtoken()});
            return (*value->value.childrens)[new_index];
        }

        bool empty(jtoken_value const* value) const override
        {
            return value->value.childrens->empty();
        }

        size_t size(jtoken_value const* value) const override
        {
            return value->value.childrens->size();
        }

        jtoken& front(jtoken_value* value) const override
        {
            if (value->value.childrens == nullptr)
                value->value.childrens = new tokens();

            if (value->value.childrens->empty())
                throw std::out_of_range("jtoken::front");

            return (*value->value.childrens)[0];
        }

        const jtoken& front(jtoken_value const* value) const override
        {
            return this->front(const_cast<jtoken_value*>(value));
        }

        jtoken& back(jtoken_value* value) const override
        {
            if (value->value.childrens == nullptr)
                value->value.childrens = new tokens();

            if (value->value.childrens->empty())
                throw std::out_of_range("jtoken::back");

            size_t size = value->value.childrens->size() - 1;
            return (*value->value.childrens)[size];
        }

        const jtoken& back(jtoken_value const* value) const override
        {
            return this->back(const_cast<jtoken_value*>(value));
        }

        iterator begin(jtoken_value* value) const override
        {
            return value->value.childrens->begin();
        }

        const_iterator cbegin(jtoken_value const* value) const override
        {
            return value->value.childrens->begin();
        }

        iterator end(jtoken_value* value) const override
        {
            return value->value.childrens->end();
        }

        const_iterator cend(jtoken_value const* value) const override
        {
            return value->value.childrens->end();
        }

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
