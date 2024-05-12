#pragma once
#include <cstring>

namespace airashe::json
{
    /**
     * @brief Index in jcontainer.
     * Represents both members of object, and indexes of array.
     */
    struct jindex
    {
    private:
        /**
         * @brief Index of element in jcontainer.
         */
        int _index;
        /**
         * @brief Name of field in jcontainer, when it's object.
         */
        char* _name;

        /**
         * @brief Set field name value.
         * @param value new name of field.
         */
        void set_name(const char* value);

    public:
        /**
         * @brief Empty index.
         */
        jindex() : _index(-1), _name(nullptr)
        {
        }

        /**
         * jindex only with index.
         * @param index index of element in jcontainer.
         */
        jindex(int const index) : _index(index), _name(nullptr)
        {
        }

        /**
         * jindex only with field name.
         * @param name name of field in jcontainer.
         */
        jindex(const char* name) : _index(-1), _name(nullptr) { set_name(name); }

        /**
         * jindex that can be found both by index and field name.
         * @param index index of field in jcontainer.
         * @param name name of filed in jcontainer.
         */
        jindex(int const index, const char* name) : _index(index), _name(nullptr) { set_name(name); }

        /**
         * Create copy.
         * @param jindex jindex to copy. 
         */
        jindex(const jindex& jindex) : _index(jindex._index), _name(nullptr) { set_name(jindex._name); }

        jindex& operator=(const jindex& jindex)
        {
            if (this == &jindex) return *this;

            _index = jindex._index;
            set_name(jindex._name);
            return *this;
        }

        friend bool operator==(const jindex& left, const jindex& right);
        friend bool operator<(const jindex& left, const jindex& right);
    };
}
