#pragma once
#include <cstring>
#include <string>

#include "jtoken_type.hpp"
#include "jtoken_value.hpp"
#include "jindex.hpp"

namespace airashe::json
{
    class jtoken_behaviour;
    struct jproperty;

    /**
     * Token of JSON structure.
     */
    struct jtoken
    {
    private:
        /**
         * Type of token.
         */
        jtoken_type _type;
        /**
         * Value of token. 
         */
        jtoken_value _value;
        /**
         * Value of last to string.
         */
        mutable std::string _lastStrVal;

    public:
        jtoken();
        jtoken(const jtoken& other);
        jtoken& operator=(const jtoken& other);
        ~jtoken();

        /**
         * Initialize string token.
         * @param string value of token.
         */
        jtoken(const char* string);

        /**
         * Get child token within container.
         * @param index index of token.
         * @return Child token.
         */
        jtoken& at(jindex index);
        jtoken& operator[](jindex index) { return at(index); }

        /**
         * Convert token to string.
         * @return Returns token as a string value.
         */
        const char* c_str() const {return to_string().c_str(); }

        /**
         * Convert token to string.
         * @return Returns token as a string value.
         */
        std::string& to_string() const;
        operator std::string() const { return to_string(); }

        /**
         * Get type of token.
         * @return Returns type of token.
         */
        jtoken_type get_type() const;

        friend jtoken jarray();
        friend jtoken jobject();
    };

    /**
     * Create JSON array token.
     * @return Returns created array.
     */
    jtoken jarray();

    /**
     * Create JSON array token.
     * @param childrens Child elements that will be put to array.
     * @return Returns created array.
     */
    jtoken jarray(std::initializer_list<jtoken> childrens);

    /**
     * Create JSON object token.
     * @return Created object.
     */
    jtoken jobject();

    /**
     * Create JSON object token.
     * @param childrens Properties that will be put to object.
     * @return Created object.
     */
    jtoken jobject(std::initializer_list<jproperty> childrens);
}
