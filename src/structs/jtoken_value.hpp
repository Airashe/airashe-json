#pragma once
#include "jtoken_value_container.hpp"

namespace airashe::json
{
    /**
     * @brief Value of JSON token.
     */
    struct jtoken_value
    {
    public:
        /**
         * @brief Value.
         */
        jtoken_value_container value;

        /**
         * @brif Modificators of value.
         */
        unsigned short modifiers;
    };
}
