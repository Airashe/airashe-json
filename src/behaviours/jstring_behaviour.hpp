#pragma once
#include <cstring>
#include "structs/jtoken_value.hpp"
#include "jtoken_behaviour.hpp"

namespace airashe::json
{
    class jstring_behaviour final : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override
        {
            delete[] value->string;
        }
        
        void assign_value(jtoken_value* target, void const* source) const override
        {
            const char* src_char = (char const*)source;
            size_t length = strlen(src_char);
            target->string = new char[length + 1];
            strcpy(target->string, src_char);
        }

        void copy_value(jtoken_value* target, jtoken_value const* source) const override
        {
            if (target == source)
				return;

            if (source->string == nullptr)
            {
				target->string = nullptr;
                return;
            }

            if (target->string != nullptr)
                delete[] target->string;

			size_t length = strlen(source->string);
			target->string = new char[length + 1];
			strcpy(target->string, source->string);
        }

        jtoken& at(jtoken_value* value, const size_t index) const override
        {
            throw std::logic_error("Can not extract jtoken from string.");
        }

        const char* c_str(jtoken_value const* value) const override
        {
            return value->string;
        }
    };
}
