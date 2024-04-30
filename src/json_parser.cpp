#include <iostream>
#include "json_parser.hpp"

namespace airashe::json
{
    void json_parser::parse(const char* json)
    {
        std::cout << "parsing: " << json << std::endl;
    }
}