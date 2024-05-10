#pragma once

namespace airashe::json
{
    union jtoken_value;

    /**
     * Interface for objects responsible for tokens behaviour in c++ code.
     */
    class jtoken_behaviour
    {
    public:
        jtoken_behaviour() = default;

        virtual ~jtoken_behaviour() = default;

        /**
         * Cleanup token.
         */
        virtual void cleanup(jtoken_value* value) const = 0;

        /**
         * Assign value from source to target JSON container.
         * @param target target JSON value container.
         * @param source source of value.
         */
        virtual void assign_value(jtoken_value* target, void const* source) const = 0;

        /**
         * Copy value from one JSON container to another.
         * @param target target JSON value container.
         * @param source source JSON value container.
         */
        virtual void copy_value(jtoken_value* target, jtoken_value const* source) const = 0;

        /**
          * Access element within value of token.
          * @param value value of token.
          * @param index index of element.
          * @return reference to element.
          */
        virtual jtoken& at(jtoken_value* value, const size_t index) const = 0;

        virtual const char* c_str(jtoken_value const* value) const = 0;
    };
}
