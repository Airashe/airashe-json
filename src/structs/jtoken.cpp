#include "jtoken.hpp"

#include "jmodifiers.hpp"
#include "jproperty.hpp"
#include "behaviours/jbehaviour_factory.hpp"

namespace airashe::json
{
    jtoken::jtoken()
    {
        set_type(jtoken_err);
        _value.value.string = nullptr;
        _value.modifiers = jmod_none;
        _lastStrVal = std::string();
    }

    jtoken::jtoken(const jtoken& other)
    {
        set_type(other._type);
        if (_type != jtoken_err)
		    _behaviour->copy_value(&_value, &other._value);
    }

    jtoken& jtoken::operator=(const jtoken& other)
    {
        if (this == &other)
            return *this;

        if(_type != jtoken_err && _type != other._type)
            _behaviour->cleanup(&_value);
        set_type(other._type);
        if (_type != jtoken_err)
            _behaviour->copy_value(&_value, &other._value);
        return *this;
    }

    jtoken::~jtoken()
    {
        if (_type != jtoken_err)
            _behaviour->cleanup(&_value);
    }

    jtoken::jtoken(const char* string)
    {
        if (string == nullptr)
        {
            set_type(jtoken_null);
            _behaviour->assign_value(&_value, string);
            return;
        }
        set_type(jtoken_string);
        _behaviour->assign_value(&_value, string);
    }

    jtoken::jtoken(const std::string& string)
    {
        set_type(jtoken_string);
        _behaviour->assign_value(&_value, string.c_str());
    }

    jtoken::jtoken(long long int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long_long;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned long long int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long_long & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(long int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned long int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_integer;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned int number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_integer & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(short number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_short;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned short number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_short & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(char number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_char;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned char number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_char & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(float number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_float;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(double number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_double;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(long double number)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_longdouble;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(bool boolean)
    {
        set_type(jtoken_boolean);
        _value.modifiers = jmod_none;
        _behaviour->assign_value(&_value, &boolean);
    }

    jtoken& jtoken::at(const jindex index)
    {
        return jbehaviour_factory::get_behaviour(_type)->at(&_value, index);
    }
    
    std::string& jtoken::to_string() const
    {
        _lastStrVal = _behaviour->to_string(&_value);
        return _lastStrVal;
    }

    long long int jtoken::to_ll() const
    {
        return _behaviour->to_ll(&_value);
    }

    unsigned long long int jtoken::to_ull() const
    {
        return _behaviour->to_ull(&_value);
    }

    long int jtoken::to_l() const
    {
        return _behaviour->to_l(&_value);
    }

    unsigned long int jtoken::to_ul() const
    {
        return _behaviour->to_ul(&_value);
    }

    int jtoken::to_i() const
    {
        return _behaviour->to_i(&_value);
    }

    short jtoken::to_s() const
    {
        return _behaviour->to_s(&_value);
    }

    unsigned short jtoken::to_us() const
    {
        return _behaviour->to_us(&_value);
    }

    char jtoken::to_c() const
    {
        return _behaviour->to_c(&_value);
    }

    unsigned char jtoken::to_uc() const
    {
        return _behaviour->to_uc(&_value);
    }

    unsigned int jtoken::to_ui() const
    {
        return _behaviour->to_ui(&_value);
    }

    float jtoken::to_f() const
    {
        return _behaviour->to_f(&_value);
    }

    double jtoken::to_d() const
    {
        return _behaviour->to_d(&_value);
    }

    long double jtoken::to_ld() const
    {
        return _behaviour->to_ld(&_value);
    }

    bool jtoken::to_bool() const
    {
        return _behaviour->to_bool(&_value);
    }
    
    void jtoken::set_type(jtoken_type type)
    {
        this->_type = type;
        this->_behaviour = jbehaviour_factory::get_behaviour(type);
    }

    jtoken jarray()
    {
        auto array = jtoken();
        array.set_type(jtoken_array);
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
        object.set_type(jtoken_object);
        object._type = jtoken_type::jtoken_object;

        return object;
    }

    jtoken jnull()
    {
        auto null = jtoken();
        null.set_type(jtoken_null);
        return null;
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
