#include "jindex.hpp"

namespace airashe::json
{
    void jindex::set_name(const char* value)
    {
        delete[] _name;
        if (value == nullptr)
        {
            _name = nullptr;
            return;
        }

        _name = new char[strlen(value) + 1];
        strcpy(_name, value);
    }

    jindex::~jindex()
    {
        delete[] _name;
    }

    bool operator==(const jindex& left, const jindex& right)
    {
        const bool some_index_is_unset = left._index == -1 || right._index == -1;
        const bool some_name_is_unset = left._name == nullptr || right._name == nullptr;

        if (some_index_is_unset && some_name_is_unset)
            return false;

        if (!some_name_is_unset)
            return strcmp(left._name, right._name) == 0;

        return left._index == right._index;
    }

    bool operator<(const jindex& left, const jindex& right)
    {
        const bool some_index_is_unset = left._index == -1 || right._index == -1;
        const bool some_name_is_unset = left._name == nullptr || right._name == nullptr;

        if (some_index_is_unset && some_name_is_unset)
            return true;

        if (!some_name_is_unset)
            return strcmp(left._name, right._name) < 0;

        return left._index < right._index;
    }
}
