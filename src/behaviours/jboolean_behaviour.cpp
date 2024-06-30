#include "jboolean_behaviour.hpp"

namespace airashe::json
{
    void jboolean_behaviour::cleanup(jtoken_value* value) const
    {
        value->modifiers = jmod_none;
        value->value.string = nullptr;
    }

    void jboolean_behaviour::assign_value(jtoken_value* target, const void* source) const
    {
        target->modifiers = jmod_none;
        if (source == nullptr)
        {
            target->value.boolean = false;
            return;
        }
            
        target->value.boolean = *(bool const*)source;
    }

    void jboolean_behaviour::copy_value(jtoken_value* target, const jtoken_value* source) const
    {
        target->modifiers = jmod_none;
        if (source == nullptr)
        {
            target->value.boolean = false;
            return;
        }

        target->modifiers = source->modifiers;
        target->value.boolean = source->value.boolean;
    }

    void jboolean_behaviour::move_value(jtoken_value* target, jtoken_value* source) const
    {
        if (target == source)
            return;

        if (source == nullptr)
        {
            target->value.boolean = false;
            return;
        }

        target->modifiers = source->modifiers;
        target->value.boolean = source->value.boolean;

        source->modifiers = jmod_none;
        source->value.string = nullptr;
    }

    void jboolean_behaviour::patch_value(jtoken_value* target, jtoken_value const* source,
        jtoken_behaviour const* source_behaviour)
    {
        if (source == nullptr)
        {
            target->modifiers = jmod_none;
            target->value.boolean = false;
            return;
        }

        if (this == source_behaviour)
        {
            copy_value(target, source);
            return;
        }

        bool b = source_behaviour->to_bool(source);
        assign_value(target, &b);
    }
}
