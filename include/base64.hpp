#ifndef _base64_hpp
#define _base64_hpp

#include <string>

std::string base64_encode(const unsigned char *src, size_t len);
std::string base64_decode(const void* data, const size_t len, size_t * lenOut);

#endif
