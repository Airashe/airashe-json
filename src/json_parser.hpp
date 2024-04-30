#pragma once

#ifdef _WIN32
  #define HELLO_EXPORT __declspec(dllexport)
#else
  #define HELLO_EXPORT
#endif

namespace airashe::json
{
  class json_parser
  {
  public: 
    void parse(const char* json);
  };
}