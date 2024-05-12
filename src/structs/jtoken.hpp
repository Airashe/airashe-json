#pragma once
#include <cstring>

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
        const char* c_str() const;

        friend jtoken jarray();
        friend jtoken jobject();
    };

    jtoken jarray();
    jtoken jarray(std::initializer_list<jtoken> childrens);

    jtoken jobject();
    jtoken jobject(std::initializer_list<jproperty> childrens);
}
