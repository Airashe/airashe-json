#include "jparser.hpp"

namespace airashe::json
{
    char jparser::next(bool peek)
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

    const char* jparser::read_value_until_end_of(jtoken_type type, jmodifiers& modifiers)
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

    jtoken_type jparser::get_type(char c)
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

    char jparser::is_end_char(char c, jtoken_type type)
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

    void jparser::parse_array(jtoken& target)
    {
        target = jarray();
        int childrens_size = 0;
        do
        {
            char peek_char = next(true);
            if (peek_char == ']')
            {
                next();
                return;
            }
            if (peek_char == ',')
            {
                next();
                continue;
            }
    
            auto child = parse();
            target[childrens_size] = child;
            childrens_size++;

            if (child.get_type() == jtoken_err)
                return;
        } while(true);
    }

    void jparser::parse_object(jtoken& target)
    {
        target = jobject();
        do
        {
            char peek_char = next(true);
            if (peek_char == '}')
            {
                next();
                return;
            }
            if (peek_char == ',')
            {
                next();
                continue;
            }

            if (!read_next_property(target))
                return;
        } while(true);
    }

    void jparser::parse_value(jtoken& target, jtoken_type type)
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

    bool jparser::read_next_property(jtoken& object)
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

    bool jparser::check_errors(jtoken& target)
    {
        if (!target.is_valid())
            return true;

        if (!is_container(target.get_type()))
            return false;

        jtoken err_token;
        bool inner_error = false;
        for (auto& [key, token] : target)
        {
            if (check_errors(token))
            {
                err_token = token.to_string();
                err_token.patch_type(jtoken_err);
                inner_error = true;
                break;
            }
        }
        if (!inner_error)
            return false;

        target = err_token;
        return true;
    }

    jparser::jparser(const char* json): _charIndex(0), _json(nullptr)
    {
        _size = strlen(json);
        if (_size == 0 || json == nullptr)
            return;

        _json = new char[_size + 1];
        memcpy(_json, json, _size);
        _json[_size] = 0;
    }

    jparser::jparser(const jparser& other)
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

    jtoken jparser::parse()
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
}
