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
         * Number as integer value.
         */
        long long int int_number;

        /**
         * Number as float value.
         */
        long double float_number;

        /**
         * Value as boolean.
         */
        bool boolean;

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
