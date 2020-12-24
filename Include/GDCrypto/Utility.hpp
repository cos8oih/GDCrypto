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

#include "GDCrypto/Export.hpp"
#include "GDCrypto/Keys.hpp"
#include "GDCrypto/Salts.hpp"

#include <cmath>
#include <array>
#include <vector>
#include <string>

namespace gdcrypto
{
	template <typename T, std::size_t const N>
	inline std::vector<T> vecFromArray(std::array<T, N> const& arr)
	{
		return std::vector<T>(
			arr.begin(),
			arr.end());
	}

	inline std::string toString(std::vector<std::uint8_t> const& buffer)
	{
		return std::string(
			buffer.begin(),
			buffer.end());
	}

	inline void xorWithKey(
		std::vector<std::uint8_t>& buffer,
		std::vector<std::uint8_t> const& key)
	{
		if (buffer.size() && key.size())
		{
			//Modulo optimization
			if (key.size() == 1)
			{
				if (buffer.front() != '\0')
				{
					for (auto& b : buffer)
						b ^= key[0];
				}
			}
			else if (key.size() == 2)
			{
				for (auto i = 0u; i < buffer.size(); ++i)
					buffer[i] ^= key[i & 1];
			}
			else
			{
				for (auto i = 0u; i < buffer.size(); ++i)
					buffer[i] ^= key[i % key.size()];
			}
		}
	}

	inline void xorWithKey(
		std::string& s,
		std::vector<std::uint8_t> const& key)
	{
		if (s.size() && key.size())
		{
			//Modulo optimization
			if (key.size() == 1)
			{
				if (s.front() != '\0')
				{
					for (auto& c : s)
						c ^= key[0];
				}
			}
			else if (key.size() == 2)
			{
				for (auto i = 0u; i < s.size(); ++i)
					s[i] ^= key[i & 1];
			}
			else
			{
				for (auto i = 0u; i < s.size(); ++i)
					s[i] ^= key[i % key.size()];
			}
		}
	}

	inline std::string levelSeed(std::string const& levelString)
	{
		std::string ret;

		if (levelString.size() < 49)
			return levelString;

		for (auto i = 0u; i < 50; ++i)
			ret += levelString[(levelString.size() / 50) * i];

		return ret;
	}

	inline std::int32_t levelscoreSeed(
		std::uint32_t const jumps,
		std::uint32_t const percentage,
		std::uint32_t const seconds)
	{
		return 1482 +
			(jumps + 3991) * (percentage + 8354)
			+ std::pow(seconds + 4085, 2) - 50028039;
	}
}

#endif /* _GDCRYPTO_UTILITY_HPP */
