#pragma once

namespace airashe::json
{
    /**
     * Modificators for json values.
     */
    enum jmodifiers : unsigned short
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
         * Long number.
         */
        jmod_number_long = 0x8,

        /**
         * Long long number.
         */
        jmod_number_long_long = 0x10,

        /**
         * Short number.
         */
        jmod_number_short = 0x20,

        /**
         * Char number.
         */
        jmod_number_char = 0x40,

        /**
         * Number is double.
         */
        jmod_number_double = 0x80,

        /**
         * Number is long double
         */
        jmod_number_longdouble = 0x100,
    };
}
