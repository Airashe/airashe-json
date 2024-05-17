#pragma once

namespace airashe::json
{
    union jtoken_value;
    struct jindex;

    /**
     * @brief Interface for objects responsible for tokens behaviour in c++ code.
     */
    class jtoken_behaviour
    {
    public:
        /**
         * @brief Interface for objects responsible for tokens behaviour in c++ code.
         */
        jtoken_behaviour() = default;

        virtual ~jtoken_behaviour() = default;

        /**
         * @brief Cleanup upon token destruction.
         */
        virtual void cleanup(jtoken_value* value) const = 0;

        /**
         * @brief Assign value from source to target JSON container.
         * @param target target JSON value container.
         * @param source source of value.
         */
        virtual void assign_value(jtoken_value* target, void const* source) const = 0;

        /**
         * @brief Copy value from one JSON container to another.
         * @param target target JSON value container.
         * @param source source JSON value container.
         */
        virtual void copy_value(jtoken_value* target, jtoken_value const* source) const = 0;

        /**
          * @brief Access element within value of token.
          * @param value value of token.
          * @param index index of element.
          * @return reference to element.
          */
        virtual jtoken& at(jtoken_value* value, jindex index) const = 0;

        /**
         * @brief Convert value to string.
         * String that returns is always <b>your responsibility</b>.
         * 
         * @param value Value to convert.
         * @return Returns string representation of value.
         */
        virtual const char* c_str(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to string.
         * @param value Value to convert.
         * @return Returns string representation of value.
         */
        virtual std::string to_string(jtoken_value const* value) const = 0;
    };
}
