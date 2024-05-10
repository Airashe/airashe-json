#include <iostream>
#include "parser.hpp"

namespace airashe::json
{
    void parser::parse(const char* json)
    {
        std::cout << "parsing: " << json << std::endl;
    }
}