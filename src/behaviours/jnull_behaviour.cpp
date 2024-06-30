#include "jnull_behaviour.hpp"

namespace airashe::json
{
    void jnull_behaviour::cleanup(jtoken_value* value) const
    {
        value->modifiers = jmod_none;
        value->value.string = nullptr;
    }

    void jnull_behaviour::assign_value(jtoken_value* target, const void* source) const
    {
        target->modifiers = jmod_none;
        target->value.string = nullptr;
    }

    void jnull_behaviour::copy_value(jtoken_value* target, const jtoken_value* source) const
    {
        target->modifiers = jmod_none;
        target->value.string = nullptr;
    }

    void jnull_behaviour::move_value(jtoken_value* target, jtoken_value* source) const
    {
        target->modifiers = jmod_none;
        target->value.string = nullptr;
    }

    void jnull_behaviour::patch_value(jtoken_value* target, jtoken_value const* source,
                                                     jtoken_behaviour const* source_behaviour)
    {
        if (target == nullptr)
            return;

        target->modifiers = jmod_none;
        target->value.string = nullptr;
    }
}