﻿#pragma once
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

        char next(bool peek = false)
        {
            size_t i = _charIndex;
            do
            {
                char c = _json[_charIndex++];
                if (is_whitespace(c))
                    continue;
                if (peek)
                    _charIndex = i;
                return c;
            }
            while (_charIndex <= _size);

            if (peek)
                _charIndex = i;
            return 0;
        }

        const char* read_value_until_end_of(jtoken_type type, jmodifiers& modifiers)
        {
            const char* start = _json + _charIndex;
            size_t read_len = 0;
            bool end_char_reached = false;
            size_t escaped_count = 0;
            
            while (_charIndex <= _size)
            {
                if (is_end_char(_json[_charIndex], type))
                {
					end_char_reached = true;
					break;
                }
                if (_json[_charIndex] == 0)
					break;
                read_len++;
                _charIndex++;
                
                if (_json[_charIndex] == '.' && (type == jtoken_number))
                    modifiers = jmod_number_longdouble;

                if (_json[_charIndex] == '\\' && (type == jtoken_string) && can_escape(_json[_charIndex + 1]))
                {
                    escaped_count++;
                    read_len += 2;
                    _charIndex += 2;
                }
            }

            if (!end_char_reached)
				return nullptr;

            if (type != jtoken_string)
            {
                char* read_value = new char[read_len + 1];
                memcpy(read_value, start, read_len);
                read_value[read_len] = 0;
                return read_value;
            }

            const size_t escaped_len = read_len - escaped_count;
            size_t escaped_index = 0;
            size_t read_index = 0;
            auto escaped_string = new char[escaped_len + 1];
            do
            {
                char current_char = start[read_index];
                if (current_char == '\\' && can_escape(start[read_index + 1]))
                {
                    escaped_string[escaped_index] = escape(start[read_index + 1]);
                    read_index++;
                }
                else
                {
                    escaped_string[escaped_index] = current_char;
                }
                escaped_index++;
                read_index++;
            } while (read_index < read_len);

            escaped_string[escaped_len] = 0;
            return escaped_string;
        }

        bool can_escape(char c) { return c == '"' || c == '\\' || c == '/' || c == 'b' || c == 'f' || c == 'n' || c == 'r' || c == 't'; }

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

        jtoken_type get_type(char c)
        {
            switch (c)
            {
            case '{':
                return jtoken_object;
            case '[':
                return jtoken_array;
            case '"':
                return jtoken_string;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                return jtoken_number;
            case 't':
            case 'f':
                return jtoken_boolean;
			case 'n':
				return jtoken_null;
            default:
                return jtoken_err;
            }
        }

        bool is_container(jtoken_type type) { return (type == jtoken_array) || (type == jtoken_object); }

        char is_end_char(char c, jtoken_type type)
        {
            switch (type)
            {
            case jtoken_array:
                return c == ']';
            case jtoken_object:
                return c == '}';
            case jtoken_string:
                return c =='"';
            default:
                return c == 0 || c == ',' || is_whitespace(c) || c == ']' || c == '}';
            }
        }

        bool is_whitespace(char c) { return c == ' ' || c == '\t' || c == '\n' || c == '\r';  }

        void parse_array(jtoken& target)
        {
            target = jarray();
            int childrens_size = 0;
            do
            {
                char peek_char = next(true);
                if (peek_char == ']')
                    return;
                if (peek_char == ',')
                {
                    _charIndex++;
                    continue;
                }
    
                auto child = parse();
                target[childrens_size] = child;
                childrens_size++;

                if (child.get_type() == jtoken_err)
                    return;
            } while(true);
        }
        
        void parse_object(jtoken& target)
        {
            target = jobject();
            do
            {
                char peek_char = next(true);
                if (peek_char == '}')
                    return;
                if (peek_char == ',')
                {
                    _charIndex++;
                    continue;
                }

                if (!read_next_property(target))
                    return;
            } while(true);
        }

        void parse_value(jtoken& target, jtoken_type type)
        {
            if (type != jtoken_string)
                _charIndex--;
            
            jmodifiers readed_modifiers = jmod_none;
            const char* readed_value = read_value_until_end_of(type, readed_modifiers);
            if (readed_value == nullptr)
            {
                target = std::string("Unexpected end of token in position: ") + std::to_string(_charIndex);
                target.patch_type(jtoken_err);
				return;
            }
            target = readed_value;
            target.patch_type(type, readed_modifiers);
            delete[] readed_value;
            if (type == jtoken_string)
            {
                _charIndex++;
            }
        }
        
        bool read_next_property(jtoken& object)
        {
            size_t _charIndexOnPropertyStart = _charIndex;
            auto property_key = parse();
            if (property_key.get_type() != jtoken_string)
            {
                property_key = "Unexpected property key in position: " + std::to_string(_charIndexOnPropertyStart);
				property_key.patch_type(jtoken_err);
                object[0] = property_key;
				return false;
            }

			char c = next();
            if (c != ':')
            {
                property_key = "Expected ':' in position: " + std::to_string(_charIndex);
                property_key.patch_type(jtoken_err);
				object[0] = property_key;
                return false;
            }
				

            auto property_value = parse();
            object[property_key.c_str()] = property_value;
        }

        bool check_errors(jtoken& target)
        {
            if (target.get_type() == jtoken_err)
                return true;

            // TODO: write functions that makes jtoken behave like standart container.
        }

    public:
        jparser(const char* json) : _charIndex(0), _json(nullptr)
        {
            _size = strlen(json);
            if (_size == 0 || json == nullptr)
                return;

            _json = new char[_size + 1];
            memcpy(_json, json, _size);
            _json[_size] = 0;
        }

        ~jparser()
        {
            delete[] _json;
        }

        jparser(const jparser& other)
        {
            _json = nullptr;
            _charIndex = other._charIndex;
            _size = other._size;
            if (other._size == 0 || other._json == nullptr)
                return;

            _json = new char[_size + 1];
            memcpy(_json, other._json, _size);
            _json[_size] = 0;
        }
        
        jtoken parse()
        {
            jtoken root = jtoken();
            char c = next();
            auto type = get_type(c);
            if (type == jtoken_err)
            {
                root = std::string("Unexpected character ") + _json[_charIndex - 1] + " in position: " + std::to_string(_charIndex);
				root.patch_type(jtoken_err);
				return root;
            }

            if (is_container(type))
            {
                if (type == jtoken_object)
                    parse_object(root);
                else
                    parse_array(root);
            }
            else
            {
                parse_value(root, type);
                return root;
            }

            check_errors(root);
            return root;
        }

        friend jtoken json(const char* json);
    };

    inline jtoken json(const char* json)
    {
        auto parser = jparser(json);
        return parser.parse();
    }
}
