#pragma once
#include "jtoken.hpp"

namespace airashe::json
{
    /**
     * Temp struct for filling jobject with properties.
     */
    struct jproperty
    {
    public:
        /**
         * Key of property.
         */
        const char* key;

        /**
         * Token associated with key.
         */
        jtoken value;

        jproperty(const char* key, jtoken token) : key(key), value(token) {}
    };
}
