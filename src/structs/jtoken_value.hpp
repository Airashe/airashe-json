#pragma once
#include <map>

namespace airashe::json
{
    struct jtoken;
    
    /**
     * Value of JSON token.
     */
    union jtoken_value
    {
    public:
        /**
         * String value.
         */
        char* string;

        /**
         * Childrens of current token.
         */
        std::map<size_t, jtoken>* childrens;

        jtoken_value()
        {
            string = nullptr;
        }
    };
}
