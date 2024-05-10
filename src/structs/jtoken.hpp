﻿#pragma once
#include <cstring>
#include <initializer_list>

#include "jtoken_type.hpp"
#include "jtoken_value.hpp"

namespace airashe::json
{
    class jtoken_behaviour;
    
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
         * Initialize json array, with list of jtokens.
         * @param list array elements.
         */
        jtoken(std::initializer_list<jtoken> list);

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
        jtoken& at(size_t index);
        jtoken& operator[](size_t index) { return at(index);}

        const char* c_str() const;
    };
}
