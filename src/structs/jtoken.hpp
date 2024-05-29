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
         * Initialize number token.
         * @param number integer value of token.
         */
        jtoken(long long int number);
        /**
         * Initialize number token.
         * @param number integer value of token.
         */
        jtoken(unsigned long long int number);
        /**
         * Initialize number token.
         * @param number integer value of token.
         */
        jtoken(long int number);
        /**
         * Initialize number token.
         * @param number integer value of token.
         */
        jtoken(unsigned long int number);

        /**
         * Initialize number token.
         * @param number float value of token.
         */
        jtoken(float number);
        /**
         * Initialize number token.
         * @param number double value of token.
         */
        jtoken(double number);
        /**
         * Initialize number token.
         * @param number long double value of token.
         */
        jtoken(long double number);

        /**
         * Get child token within container.
         * @param index index of token.
         * @return Child token.
         */
        jtoken& at(jindex index);
        jtoken& operator[](const char* index) { return at(index); }
        jtoken& operator[](int index) { return at(index); }

        /**
         * Convert token to string.
         * @return Returns token as a string value.
         */
        const char* c_str() const { return to_string().c_str(); }
        operator const char*() const { return c_str(); }

        /**
         * Convert token to string.
         * @return Returns token as a string value.
         */
        std::string& to_string() const;
        operator std::string() const { return to_string(); }

        /**
         * Convert token to long long integer.
         * @return Value of token.
         */
        long long int to_ll() const;
        operator long long int() const { return to_ll(); }

        /**
         * Convert token to unsigned long long integer.
         * @return Value of token.
         */
        unsigned long long int to_ull() const;
        operator unsigned long long int() const { return to_ull(); }

        /**
         * Convert token to long.
         * @return Value of token.
         */
        long int to_l() const;
        operator long int() const { return to_l(); }

        /**
         * Convert token to unsigned long.
         * @return Value of token.
         */
        unsigned long int to_ul() const;
        operator unsigned long int() const { return to_ul(); }

        /**
         * Convert token to integer.
         * @return Value of token.
         */
        int to_i() const;
        operator int() const { return to_i(); }

        short to_s() const;
        operator short() const { return to_s(); }

        unsigned short to_us() const;
        operator unsigned short() const { return to_us(); }

        char to_c() const;
        operator char() const { return to_c(); }

        unsigned char to_uc() const;
        operator unsigned char() const { return to_uc(); }

        /**
         * Convert token to unsigned integer.
         * @return Value of token.
         */
        unsigned int to_ui() const;
        operator unsigned int() const { return to_ui(); }

        /**
         * Convert token to float.
         * @return Value of token.
         */
        float to_f() const;
        operator float() const { return to_f(); }

        /**
         * Convert token to double.
         * @return Value of token.
         */
        double to_d() const;
        operator double() const { return to_d(); }

        /**
         * Convert token to long double.
         * @return Value of token.
         */
        long double to_ld() const;

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
