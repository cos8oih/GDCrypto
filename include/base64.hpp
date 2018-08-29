#ifndef _base64_hpp
#define _base64_hpp

#include <string>
#include <vector>
#include <iterator>

std::string Base64_Encode(const std::vector<unsigned char>& Src);
std::vector<unsigned char> Base64_Decode(const std::string& Src);

#endif
