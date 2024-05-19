#include "jtoken.hpp"

#include <iostream>

#include "jproperty.hpp"
#include "behaviours/jbehaviour_factory.hpp"

namespace airashe::json
{
    jtoken::jtoken()
    {
        _type = jtoken_err;
        _value.value.string = nullptr;
        _value.modifiers = 0x0;
    }

    jtoken::jtoken(const jtoken& other)
    {
        _type = other._type;
        if (_type != jtoken_err)
		    jbehaviour_factory::get_behaviour(_type)->copy_value(&_value, &other._value);
    }

    jtoken& jtoken::operator=(const jtoken& other)
    {
        if (this == &other)
            return *this;

        _type = other._type;
        if (_type != jtoken_err)
            jbehaviour_factory::get_behaviour(_type)->copy_value(&_value, &other._value);
        return *this;
    }

    jtoken::~jtoken()
    {
        if (_type != jtoken_err)
        jbehaviour_factory::get_behaviour(_type)->cleanup(&_value);
    }

    jtoken::jtoken(const char* string)
    {
        _type = jtoken_type::jtoken_string;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, string);
    }

    jtoken& jtoken::at(const jindex index)
    {
        return jbehaviour_factory::get_behaviour(_type)->at(&_value, index);
    }

    std::string& jtoken::to_string() const
    {
        _lastStrVal = jbehaviour_factory::get_behaviour(_type)->to_string(&_value);
        return _lastStrVal;
    }

    jtoken_type jtoken::get_type() const
    {
        return _type;
    }

    jtoken jarray()
    {
        auto array = jtoken();
        array._type = jtoken_type::jtoken_array;
        return array;
    }

    jtoken jarray(const std::initializer_list<jtoken> childrens)
    {
        auto array = jarray();
        const jtoken* children = childrens.begin();
        for(int i = 0; i < childrens.size(); i++)
            array[i] = children[i];

        return array;
    }

    jtoken jobject()
    {
        auto object = jtoken();
        object._type = jtoken_type::jtoken_object;

        return object;
    }

    jtoken jobject(const std::initializer_list<jproperty> childrens)
    {
        auto object = jobject();
        const jproperty* children = childrens.begin();
        for(auto& property : childrens)
            object[property.key] = property.value;

        return object;
    }
}
