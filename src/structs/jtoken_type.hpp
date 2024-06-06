#pragma once

namespace airashe::json
{
    /**
     * @brief Type of JSON token.
     */
    enum jtoken_type : unsigned char
    {
        /**
         * @brief String.
         */
        jtoken_string = 0x1,

        /**
         * @brief Array.
         */
        jtoken_array = 0x2,

        /**
         * @brief Object.
         */
        jtoken_object = 0x4,

        /**
         * @brief Number.
         */
        jtoken_number = 0x8,

        /**
         * @brief Boolean.
         */
        jtoken_boolean = 0x10, 
     
        /**
         * @brief Invalid token.
         */
        jtoken_err = 0xFF, 
    };
}
