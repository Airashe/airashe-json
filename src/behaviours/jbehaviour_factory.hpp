#pragma once
#include <map>

#include "jarray_behaviour.hpp"
#include "jboolean_behaviour.hpp"
#include "jcontainer_behaviour.hpp"
#include "jnull_behaviour.hpp"
#include "jnumber_behaviour.hpp"
#include "jstring_behaviour.hpp"

namespace airashe::json
{
    class jtoken_behaviour;
    enum jtoken_type : unsigned char;

    /**
     * @brief Factory to get behaviour instances for tokens.
     */
    class jbehaviour_factory final
    {
    private:
        inline static jtoken_behaviour* _str_behaviour = new jstring_behaviour;
        
        /**
         * @brief Behaviour instances.
         */
        inline static std::map<jtoken_type, jtoken_behaviour*> _behaviours = {
            {jtoken_err, _str_behaviour}, 
            {jtoken_string, _str_behaviour},
            {jtoken_array, new jarray_behaviour},
            {jtoken_object, new jcontainer_behaviour},
            {jtoken_number, new jnumber_behaviour},
            {jtoken_boolean, new jboolean_behaviour},
            {jtoken_null, new jnull_behaviour}
        };
    public:
        /**
         * @brief Get token behaviour based on token type.
         * @param type type of token.
         * @return 
         */
        static jtoken_behaviour* get_behaviour(jtoken_type const type)
        {
            if (_behaviours.contains(type))
				return _behaviours[type];
            return nullptr;
        }
    };
}
