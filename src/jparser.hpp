#pragma once
#include "structs/jtoken.hpp"
#include <iostream>
#include <structs/jmodifiers.hpp>

namespace airashe::json
{
    class jparser
    {
    private:
        size_t _charIndex;
        char* _json;
        size_t _size;

        char next(bool peek = false);

        const char* read_value_until_end_of(jtoken_type type, jmodifiers& modifiers);

        bool can_escape(char c)
        {
            return c == '"' || c == '\\' || c == '/' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't';
        }

        char escape(char c)
        {
            switch(c)
            {
            case '"':
                return '"';
            case '\\':
                return '\\';
            case '/':
                return '/';
            case 'b':
                return '\b';
            case 'f':
                return '\f';
            case 'n':
                return '\n';
            case 'r':
                return '\r';
            case 't':
                return '\t';
            default:
                return 0;
            }
        }

        jtoken_type get_type(char c);

        bool is_container(jtoken_type type) { return (type == jtoken_array) || (type == jtoken_object); }

        char is_end_char(char c, jtoken_type type);

        bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r';  }

        void parse_array(jtoken& target);

        void parse_object(jtoken& target);

        void parse_value(jtoken& target, jtoken_type type);

        bool read_next_property(jtoken& object);

        bool check_errors(jtoken& target);

    public:
        jparser(const char* json);

        ~jparser()
        {
            delete[] _json;
        }

        jparser(const jparser& other);

        jtoken parse();

        friend jtoken json(const char* json);
    };

    inline jtoken json(const char* json)
    {
        auto parser = jparser(json);
        return parser.parse();
    }
}
