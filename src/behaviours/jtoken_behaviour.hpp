﻿#pragma once
#include <stdexcept>
#include <map>

#include "structs/jmodifiers.hpp"
#include "structs/jtoken_value.hpp"
#include "structs/jindex.hpp"

namespace airashe::json
{
    struct jtoken;
    struct jtoken_value;
    struct jindex;

    /**
     * @brief Interface for objects responsible for tokens behaviour in c++ code.
     */
    class jtoken_behaviour
    {
    protected:
        bool has_flag(const jtoken_value* value, jmodifiers flag) const
        {
            return (value->modifiers | flag) == value->modifiers;
        }

        bool in_mask(const jtoken_value* value, int mask) const
        {
            return (value->modifiers & mask) > 0;
        }

    public:
        typedef typename std::map<jindex, jtoken>::iterator iterator;
        typedef typename std::map<jindex, jtoken>::const_iterator const_iterator;

        /**
         * @brief Interface for objects responsible for tokens behaviour in c++ code.
         */
        jtoken_behaviour() = default;

        jtoken_behaviour(const jtoken_behaviour&) = delete;
        jtoken_behaviour& operator=(const jtoken_behaviour&) = delete;
        jtoken_behaviour(jtoken_behaviour&&) = delete;
        jtoken_behaviour& operator=(jtoken_behaviour&&) = delete;

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
         * Perform move operation on value.
         * @param target new owner of resources.
         * @param source old owner.
         */
        virtual void move_value(jtoken_value* target, jtoken_value* source) const = 0;

        /**
         * Convert value of other type to current.
         * @param target target where value will be stored.
         * @param source source of value to convert.
         * @param source_behaviour behaviour of source.
         */
        virtual void patch_value(jtoken_value* target, jtoken_value const* source,
                                 jtoken_behaviour const* source_behaviour) = 0;

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
         * @brief Check if value is empty (in case of containers check as STL container).
         * @param value Value of token.
         * @return Returns true if value is empty, otherwise false.
         */
        virtual bool empty(jtoken_value const* value) const
        {
            throw std::logic_error("Not implemented");
        }

        /**
         * @brief Get size of value (only for containers).
         * @param value Value of token.
         * @return Return elements count in value.
         */
        virtual size_t size(jtoken_value const* value) const
        {
            throw std::logic_error("Not implemented");
        }

        /**
         * @brief Get first element of token.
         * @param value Value of token.
         * @return Returns first element of token.
         */
        virtual jtoken& front(jtoken_value* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual const jtoken& front(jtoken_value const* value) const
        {
            throw std::logic_error("Not implemented");
        }

        /**
            * @brief Get last element of token.
            * @param value Value of token.
            * @return Returns last element of token.
            */
        virtual jtoken& back(jtoken_value* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual const jtoken& back(jtoken_value const* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual iterator begin(jtoken_value* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual const_iterator cbegin(jtoken_value const* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual iterator end(jtoken_value* value) const
        {
            throw std::logic_error("Not implemented");
        }

        virtual const_iterator cend(jtoken_value const* value) const
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
         * @brief Convert value to integer.
         * @param value Value to extract.
         * @return Value as integer.
         */
        virtual int to_i(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to unsigned integer.
         * @param value Value of token.
         * @return Return unsigned integer.
         */
        virtual unsigned int to_ui(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to short integer.
         * @param value Value to extract.
         * @return Value as short integer.
         */
        virtual short to_s(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to unsigned short integer.
         * @param value Value of token.
         * @return Return unsigned short integer.
         */
        virtual unsigned short to_us(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to char.
         * @param value Value to extract.
         * @return Value as char.
         */
        virtual char to_c(jtoken_value const* value) const = 0;

        /**
         * @brief Convert value to unsigned char.
         * @param value Value of token.
         * @return Return unsigned char.
         */
        virtual unsigned char to_uc(jtoken_value const* value) const = 0;

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

        /**
         * Convert value to boolean.
         * @param value Value to extract.
         * @return Value as boolean.
         */
        virtual bool to_bool(jtoken_value const* value) const = 0;
    };
}
