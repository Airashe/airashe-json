#pragma once
#include <map>

namespace airashe::json
{
    struct jtoken;
    struct jindex;
    
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
        std::map<jindex, jtoken>* childrens;

        jtoken_value()
        {
            string = nullptr;
        }
    };
}
