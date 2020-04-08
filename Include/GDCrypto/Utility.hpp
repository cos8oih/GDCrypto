#ifndef _GDCRYPTO_UTILITY_HPP
#define _GDCRYPTO_UTILITY_HPP

#include "Include/GDCrypto/Export.hpp"

#include <cmath>
#include <vector>
#include <string>

namespace gdcrypto
{
	GDCRYPTO_API inline void xorWithKey(
		std::vector<uint8_t>& buffer,
		std::vector<uint8_t> const& key)
	{
		//Xor with { '\0' } has no effect
		if (buffer.size() && key.size() &&
			!(buffer.size() == 1 &&
				buffer.front() == '\0'))
		{
			for (auto i = 0u; i < buffer.size(); ++i)
				buffer[i] ^= key[i % key.size()];
		}
	}

	GDCRYPTO_API inline void xorWithKey(
		std::string& s,
		std::vector<uint8_t> const& key)
	{
		//Xor with { '\0' } has no effect
		if (s.size() && key.size() &&
			!(s.size() == 1 &&
				s.front() == '\0'))
		{
			for (auto i = 0u; i < s.size(); ++i)
				s[i] ^= key[i % key.size()];
		}
	}

	GDCRYPTO_API inline std::string levelSeed(
		std::string const& levelString)
	{
		std::string ret;

		if (levelString.size() < 49)
			return levelString;

		for (auto i = 0u; i < 50; ++i)
			ret += levelString[(levelString.size() / 50) * i];

		return ret;
	}

	GDCRYPTO_API inline int32_t levelscoreSeed(
		uint32_t const jumps,
		uint32_t const percentage,
		uint32_t const seconds)
	{
		return 1482 +
			(jumps + 3991) * (percentage + 8354)
			+ std::pow(seconds + 4085, 2) - 50028039;
	}
}

#endif /* _GDCRYPTO_UTILITY_HPP */
