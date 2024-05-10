#pragma once

namespace airashe::json
{
    /**
     * Type of JSON token.
     */
    enum jtoken_type : unsigned char
    {
        /**
         * String.
         */
        jtoken_string = 0x1,

        /**
         * Array.
         */
        jtoken_array = 0x2, 

        /**
         * Invalid token.
         */
        jtoken_err = 0xFF, 
    };
}
