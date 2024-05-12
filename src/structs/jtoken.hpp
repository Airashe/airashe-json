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

        /**
         * Create JSON array.
         * @return Returns token with array type.
         */
        template <typename... Args, typename=jtoken>
        friend jtoken jarray();

        /**
         * Create JSON array.
         * @param args Tokens to add to array.
         * @return Returns token with array type.
         */
        template <typename... Args, typename=jtoken>
        friend jtoken jarray(Args... args);
    };

    template <typename... Args, typename>
    jtoken jarray()
    {
        jtoken array = jtoken();
        array._type = jtoken_array;
        return array;
    }

    template <typename... Args, typename>
    jtoken jarray(Args... args)
    {
        auto array = jarray();

        if (sizeof ...(args) > 0)
        {
            int i = 0;
            for (const auto p : {args...})
            {
                array[i] = p;
                i++;
            }
        }

        return array;
    }
}
