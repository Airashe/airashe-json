#pragma once
#include <cstring>
#include <string>

#include "jtoken_type.hpp"
#include "jtoken_value.hpp"
#include "jindex.hpp"
#include "jmodifiers.hpp"

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
         * Behaviour of token.
         */
        jtoken_behaviour* _behaviour;
        /**
         * Value of token. 
         */
        jtoken_value _value;
        /**
         * Value of last to string.
         */
        mutable std::string _lastStrVal;

        /**
            * Set type of token.
            * @param type Type of token.
            */
        void set_type(jtoken_type type);

    public:
        typedef typename std::map<jindex, jtoken>::iterator iterator;
        typedef typename std::map<jindex, jtoken>::const_iterator const_iterator;

        jtoken();
        jtoken(const jtoken& other);
        jtoken& operator=(const jtoken& other);
        jtoken(jtoken&& other) noexcept;
        jtoken& operator=(jtoken&& other) noexcept;
        ~jtoken();

        jtoken(const char* string);
        jtoken(const std::string& string);
        jtoken(long long int number);
        jtoken(unsigned long long int number);
        jtoken(long int number);
        jtoken(unsigned long int number);
        jtoken(int number);
        jtoken(unsigned int number);
        jtoken(short number);
        jtoken(unsigned short number);
        jtoken(char number);
        jtoken(unsigned char number);

        jtoken(float number);
        jtoken(double number);
        jtoken(long double number);

        jtoken(bool boolean);

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
        operator long double() const { return to_ld(); }

        /**
         * Convert token to logical value.
         * @return Return value of a token as boolean.
         */
        bool to_bool() const;
        operator bool() const { return to_bool(); }

        bool is_valid() const;

        /**
         * Get type of token.
         * @return Returns type of token.
         */
        jtoken_type get_type() const { return _type; }

        /**
         * Change token type and save value.
         * @param type New type of token.
         * @param type Modificators of new value.
         */
        void patch_type(jtoken_type type, jmodifiers modifiers = jmod_none);

        friend jtoken jarray();
        friend jtoken jarray(const std::initializer_list<jtoken>& childrens);
        friend jtoken jobject();
        friend jtoken jobject(const std::initializer_list<jproperty>& childrens);
        friend jtoken jnull();

        // container functions
        /**
         * Get child token within container.
         * @param index index of token.
         * @return Child token.
         */
        jtoken& at(jindex index);
        jtoken& operator[](const char* index) { return at(index); }
        jtoken& operator[](int index) { return at(index); }

        bool empty() const;
        size_t size() const;
        jtoken& front();
        const jtoken& front() const;
        jtoken& back();
        const jtoken& back() const;
        iterator begin() noexcept;
        const_iterator cbegin() const noexcept;
        iterator end() noexcept;
        const_iterator cend() const noexcept;
    };

    /**
     * Create JSON null token.
     * @return Returns created token.
     */
    jtoken jnull();

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
    jtoken jarray(const std::initializer_list<jtoken>& childrens);

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
    jtoken jobject(const std::initializer_list<jproperty>& childrens);
}
