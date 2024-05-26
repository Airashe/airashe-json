#pragma once

namespace airashe::json
{
    /**
     * Modificators for json values.
     */
    enum jmodifiers : unsigned char
    {
        /**
         * No modifiers applied.
         */
        jmod_none = 0x0,

        /**
         * Number is unsigned.
         */
        jmod_number_unsigned = 0x1,

        /**
         * Number is float.
         */
        jmod_number_float = 0x2,

        /**
         * Number is integer.
         */
        jmod_number_integer = 0x4,

        /**
         * Number is double.
         */
        jmod_number_double = 0x8,

        /**
         * Number is long double
         */
        jmod_number_longdouble = 0x10,
    };
}
