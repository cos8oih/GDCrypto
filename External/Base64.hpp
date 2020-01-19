#ifndef _Base64_hpp
#define _Base64_hpp

#include <vector>

namespace Base64
{
	std::vector<uint8_t> encode(std::vector<uint8_t> const& buffer);
	std::vector<uint8_t> decode(std::vector<uint8_t> const& buffer);
}

#endif /* _Base64_hpp */