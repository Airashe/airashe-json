#pragma once
#include "jtoken_behaviour.hpp"
#include "structs/jtoken_value.hpp"
#include "structs/jtoken.hpp"

namespace airashe::json
{
    class jarray_behaviour final : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override
        {
            delete value->childrens;
        }
        
        void assign_value(jtoken_value* target, const void* source) const override
        {
            const size_t size = ((std::initializer_list<jtoken>*)source)->size();
            const auto list = ((std::initializer_list<jtoken>*)source)->begin();
            
            target->childrens = new std::map<size_t, jtoken>();
            for(size_t i = 0; i < size; i++)
                (*target->childrens)[i] = list[i];
        }
        
        void copy_value(jtoken_value* target, const jtoken_value* source) const override
        {
            if (target == source)
                return;

            if (source->childrens == nullptr || source->childrens->empty())
            {
				target->childrens = new std::map<size_t, jtoken>();
                return;
            }

            for(auto it = source->childrens->begin(); it != source->childrens->end(); it++)
				(*target->childrens)[it->first] = it->second;
        }

        jtoken& at(jtoken_value* value, const size_t index) const override
        {
            if (index < 0 || index >= value->childrens->size())
                throw std::out_of_range("Requested index was outside of array.");
            
            return value->childrens->at(index);
        }

        const char* c_str(const jtoken_value* value) const override
        {
            return "[]";
        }
    };
}
