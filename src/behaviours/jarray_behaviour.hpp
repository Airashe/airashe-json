#pragma once
#include "jcontainer_behaviour.hpp"

namespace airashe::json
{
    /**
     * @brief Specific behaviour for arrays.
     */
    class jarray_behaviour final : public jcontainer_behaviour
    {
    public:
        jarray_behaviour() : jcontainer_behaviour()
        {
            _start_char = '[';
            _end_char = ']';
        }
    };
}
