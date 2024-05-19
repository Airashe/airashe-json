#pragma once
#include <cstring>
#include "structs/jtoken_value.hpp"
#include "jtoken_behaviour.hpp"

namespace airashe::json
{
    /**
     * @brief Behaviour for string tokens.
     */
    class jstring_behaviour final : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override
        {
            delete[] value->value.string;
        }
        
        void assign_value(jtoken_value* target, void const* source) const override
        {
            const char* src_char = (char const*)source;
            size_t length = strlen(src_char);
            target->value.string = new char[length + 1];
            strcpy(target->value.string, src_char);
            target->modifiers = 0x0;
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            if (target == source)
				return;

            if (source->value.string == nullptr)
            {
				target->value.string = nullptr;
                target->modifiers = 0x0;
                return;
            }

            if (target->value.string != nullptr)
                delete[] target->value.string;

			size_t length = strlen(source->value.string);
			target->value.string = new char[length + 1];
			strcpy(target->value.string, source->value.string);
            target->modifiers = source->modifiers;
        }

        jtoken& at(jtoken_value* value, const jindex index) const override
        {
            throw std::logic_error("Can not extract jtoken from string.");
        }

        std::string to_string(jtoken_value const* value) const override
        {
            return {value->value.string};
        }
    };
}
