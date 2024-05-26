#pragma once

namespace airashe::json
{
    struct jtoken_value;
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
        virtual jtoken& at(jtoken_value* value, jindex index) const
        {
            throw std::logic_error("Not implemented");
        }

        /**
         * @brief Convert value to string.
         * @param value Value to convert.
         * @return Returns string representation of value.
         */
        virtual std::string to_string(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to long long integer.
         * @param value Value to extract.
         * @return Value as long long integer.
         */
        virtual long long int to_ll(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to unsigned long long integer.
         * @param value Value of token.
         * @return Return unsigned long long integer.
         */
        virtual unsigned long long int to_ull(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to long long integer.
         * @param value Value to extract.
         * @return Value as long long integer.
         */
        virtual long int to_l(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to unsigned long long integer.
         * @param value Value of token.
         * @return Return unsigned long long integer.
         */
        virtual unsigned long int to_ul(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to float.
         * @param value Value to extract.
         * @return Value as float.
         */
        virtual float to_f(jtoken_value const* value) const = 0;
        /**
         * @brief Convert value to double.
         * @param value Value to extract.
         * @return Value as double.
         */
        virtual double to_d(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to long double.
         * @param value Value to extract.
         * @return Value as long double.
         */
        virtual long double to_ld(jtoken_value const* value) const = 0;
    };
}
