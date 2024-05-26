#include "jtoken.hpp"

#include <iostream>

#include "jmodifiers.hpp"
#include "jproperty.hpp"
#include "behaviours/jbehaviour_factory.hpp"

namespace airashe::json
{
    jtoken::jtoken()
    {
        _type = jtoken_err;
        _value.value.string = nullptr;
        _value.modifiers = jmod_none;
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

        if(_type != jtoken_err && _type != other._type)
            jbehaviour_factory::get_behaviour(_type)->cleanup(&_value);
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
        _type = jtoken_string;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, string);
    }

    jtoken::jtoken(long long int number)
    {
        _type = jtoken_number;
        _value.modifiers = jmod_number_integer;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned long long int number)
    {
        _type = jtoken_number;
        _value.modifiers = jmod_number_integer & jmod_number_unsigned;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &number);
    }

    jtoken::jtoken(float number)
    {
        _type = jtoken_number;
        _value.modifiers = jmod_number_float;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &number);
    }

    jtoken::jtoken(double number)
    {
        _type = jtoken_number;
        _value.modifiers = jmod_number_double;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &number);
    }

    jtoken::jtoken(long double number)
    {
        _type = jtoken_number;
        _value.modifiers = jmod_number_longdouble;
        jbehaviour_factory::get_behaviour(_type)->assign_value(&_value, &number);
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

    long long int jtoken::to_ll() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_ll(&_value);
    }

    unsigned long long int jtoken::to_ull() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_ull(&_value);
    }

    long int jtoken::to_l() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_l(&_value);
    }

    unsigned long int jtoken::to_ul() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_ul(&_value);
    }

    float jtoken::to_f() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_f(&_value);
    }

    double jtoken::to_d() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_d(&_value);
    }

    long double jtoken::to_ld() const
    {
        return jbehaviour_factory::get_behaviour(_type)->to_ld(&_value);
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
            object.at(property.key) = property.value;

        return object;
    }
}
