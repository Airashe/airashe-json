#include "jtoken.hpp"

#include <iostream>

#include "behaviours/jbehaviour_factory.hpp"

namespace airashe::json
{
    jtoken::jtoken(const jtoken& other)
    {
        _type = other._type;
    }

    jtoken& jtoken::operator=(const jtoken& other)
    {
        if (this == &other)
            return *this;

        _type = other._type;
        jbehaviour_factory::get_behaviour(_type)->copy_value(&_value, &other._value);
        return *this;
    }

    jtoken::~jtoken() { jbehaviour_factory::get_behaviour(_type)->cleanup(&_value); }
    
    jtoken::jtoken(std::initializer_list<jtoken> list)
    {
        _type = jtoken_type::jtoken_array;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &list);
    }

    jtoken::jtoken(const char* string)
    {
        _type = jtoken_type::jtoken_string;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, string);
    }
}
