#pragma once
#include <map>

namespace airashe::json
{
    struct jtoken;
    struct jindex;
    
    /**
     * Container to store value of JSON token.
     */
    union jtoken_value_container
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

        jtoken_value_container()
        {
            string = nullptr;
        }
    };
}
