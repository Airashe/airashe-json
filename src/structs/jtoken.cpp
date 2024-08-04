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
        _lastStrVal = nullptr;
    }

    jtoken::jtoken(const jtoken& other) : _lastStrVal(nullptr)
    {
        set_type(other._type);
		_behaviour->copy_value(&_value, &other._value);
    }

    jtoken& jtoken::operator=(const jtoken& other)
    {
        if (this == &other)
            return *this;

        if(_type != other._type)
            _behaviour->cleanup(&_value);
        set_type(other._type);
        _behaviour->copy_value(&_value, &other._value);
        return *this;
    }

    jtoken::jtoken(jtoken&& other) noexcept : _lastStrVal(nullptr)
    {
        set_type(other._type);
        _behaviour->move_value(&_value, &other._value);
        _lastStrVal = other._lastStrVal;
        other._lastStrVal = nullptr;
    }

    jtoken& jtoken::operator=(jtoken&& other) noexcept
    {
        if (this == &other)
            return *this;

        if(_type != other._type)
            _behaviour->cleanup(&_value);
        set_type(other._type);
        _behaviour->move_value(&_value, &other._value);
        
        _lastStrVal = other._lastStrVal;
        other._lastStrVal = nullptr;
        
        return *this;
    }

    jtoken::~jtoken()
    {
        _behaviour->cleanup(&_value);
        delete[] _lastStrVal;
        _lastStrVal = nullptr;
    }

    jtoken::jtoken(const char* string) : _lastStrVal(nullptr)
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

    jtoken::jtoken(const std::string& string) : _lastStrVal(nullptr)
    {
        set_type(jtoken_string);
        _behaviour->assign_value(&_value, string.c_str());
    }

    jtoken::jtoken(long long int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long_long;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned long long int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long_long & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(long int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned long int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_long & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_integer;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned int number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_integer & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(short number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_short;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned short number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_short & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(char number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_char;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(unsigned char number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_char & jmod_number_unsigned;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(float number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_float;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(double number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_double;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(long double number) : _lastStrVal(nullptr)
    {
        set_type(jtoken_number);
        _value.modifiers = jmod_number_longdouble;
        _behaviour->assign_value(&_value, &number);
    }

    jtoken::jtoken(bool boolean) : _lastStrVal(nullptr)
    {
        set_type(jtoken_boolean);
        _value.modifiers = jmod_none;
        _behaviour->assign_value(&_value, &boolean);
    }

    const char* jtoken::c_str() const
    {
        auto str = _behaviour->to_string(&_value);
        size_t len = str.size();
        if (_lastStrVal != nullptr && strcmp(str.c_str(), _lastStrVal) == 0)
            return _lastStrVal;

        delete[] _lastStrVal;
        _lastStrVal = new char[len + 1];
        memcpy(_lastStrVal, str.c_str(), len);
        _lastStrVal[len] = '\0';
        return _lastStrVal;
    }
    
    std::string jtoken::to_string() const
    {
        const char* orig = c_str();
        if (orig == nullptr)
            return "";

        const size_t len = strlen(orig);
        char* copy = new char[len];
        memcpy(copy, orig, len);
        copy[len] = '\0';
        
        return std::string { copy };
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

    bool jtoken::is_valid() const
    {
        return _type != jtoken_err;
    }

    void jtoken::patch_type(jtoken_type type, jmodifiers modifiers)
    {
        if (type == _type)
            return;
        
        auto old_behaviour = _behaviour;
        jtoken_value old_value;
        old_behaviour->copy_value(&old_value, &_value);
        old_behaviour->cleanup(&_value);
        
        set_type(type);
        _value.modifiers = modifiers;

        _behaviour->patch_value(&_value, &old_value, old_behaviour);
        old_behaviour->cleanup(&old_value);
    }

    void jtoken::set_type(jtoken_type type)
    {
        this->_type = type;
        this->_behaviour = jbehaviour_factory::get_behaviour(type);
    }

    jtoken& jtoken::at(const jindex index)
    {
        return this->_behaviour->at(&_value, index);
    }
    
    bool jtoken::empty() const
    {
        return this->_behaviour->empty(&_value);
    }

    size_t jtoken::size() const
    {
        return this->_behaviour->size(&_value);
    }

    jtoken& jtoken::front()
    {
        return this->_behaviour->front(&_value);
    }

    const jtoken& jtoken::front() const
    {
        return this->_behaviour->front(&_value);
    }

    jtoken& jtoken::back()
    {
        return this->_behaviour->back(&_value);
    }

    const jtoken& jtoken::back() const
    {
        return this->_behaviour->back(&_value);
    }

    jtoken::iterator jtoken::begin() noexcept
    {
        return this->_behaviour->begin(&_value);
    }

    jtoken::const_iterator jtoken::cbegin() const noexcept
    {
        return this->_behaviour->cbegin(&_value);
    }

    jtoken::iterator jtoken::end() noexcept
    {
        return this->_behaviour->end(&_value);
    }

    jtoken::const_iterator jtoken::cend() const noexcept
    {
        return this->_behaviour->cend(&_value);
    }

    jtoken jarray()
    {
        auto array = jtoken();
        array.set_type(jtoken_array);
        return array;
    }

    jtoken jarray(const std::initializer_list<jtoken>& childrens)
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

    jtoken jobject(const std::initializer_list<jproperty>& childrens)
    {
        auto object = jobject();
        const jproperty* children = childrens.begin();
        for(auto& property : childrens)
            object.at(property.key) = property.value;

        return object;
    }
}
