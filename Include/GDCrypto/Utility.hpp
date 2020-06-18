/*
	MIT License

	Copyright (c) 2020 Cos8o

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/
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
