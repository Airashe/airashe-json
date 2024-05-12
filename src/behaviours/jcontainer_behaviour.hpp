#pragma once
#include "jtoken_behaviour.hpp"
#include "structs/jtoken.hpp"

namespace airashe::json
{
    class jcontainer_behaviour final : public jtoken_behaviour
    {
    public:
        void cleanup(jtoken_value* value) const override { delete value->childrens; }
        
        void assign_value(jtoken_value* target, const void* source) const override
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
            for(int i = 0; i < src->childrens->size(); i++)
				target->childrens->insert({i, src->childrens->at(i)});
        }
        
        void copy_value(jtoken_value* target, const jtoken_value* source) const override
        {
            assign_value(target, source);
        }
        
        const char* c_str(const jtoken_value* value) const override
        {
            return "[]";    
        }
        
        jtoken& at(jtoken_value* value, const jindex index) const override
        {
            if(value->childrens == nullptr)
                value->childrens = new std::map<jindex, jtoken>();
            
            for(auto& child : *value->childrens)
                if (child.first == index)
                    return child.second;
            
            value->childrens->insert({index, jtoken()});
            return value->childrens->at(index);
        }
    };
}
