#pragma once
#include <map>

#include "jcontainer_behaviour.hpp"
#include "jstring_behaviour.hpp"

namespace airashe::json
{
    class jtoken_behaviour;
    enum jtoken_type : unsigned char;

    /**
     * Factory to get behaviour insances for tokens.
     */
    class jbehaviour_factory final
    {
    private:
        /**
         * Behaviour instances.
         */
        inline static std::map<jtoken_type, jtoken_behaviour*> _behaviours = {
            {jtoken_string, new jstring_behaviour},
            {jtoken_array, new jcontainer_behaviour},
            {jtoken_object, new jcontainer_behaviour}
        };
    public:
        /**
         * Get token behaviour based on token type.
         * @param type type of token.
         * @return 
         */
        static jtoken_behaviour* get_behaviour(jtoken_type type)
        {
            if (_behaviours.contains(type))
				return _behaviours[type];
            return nullptr;
        }
    };
}
