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
#ifndef _GDCRYPTO_CHECKGENERATOR_HPP
#define _GDCRYPTO_CHECKGENERATOR_HPP

#include "GDCrypto/Utility.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace gdcrypto
{
	/*
		CheckGenerator

		Checks (chk, sometimes seed2) are encoded strings that contains data
		used by the server to validate requests. Every check is encoded in this way:
		Raw data -> SHA1 string -> RobTop Cipher (every check has a different key).
		The raw data is a combination of various values and a salt, which
		also differs between checks.
	*/
	class CheckGenerator
	{
		std::vector<std::uint8_t> m_Buffer;
		std::vector<std::uint8_t> m_Key;
		std::string m_Salt;
		std::vector<std::uint8_t> m_Last;
	public:
		CheckGenerator(
			std::vector<std::uint8_t> const& key,
			std::string const& salt)
			: m_Key(key),
			m_Salt(salt) {}

		void insert(std::vector<std::uint8_t> const& buffer);
		void insert(std::string const& s);
		void insert(std::istream& in);

		void digest(std::vector<std::uint8_t>& buffer);
		void digest(std::string& s);
		void digest(std::ostream& out);

		std::string generate(std::vector<std::vector<std::uint8_t>> const& buffers);
		std::string generate(std::vector<std::string> const& buffers);

		std::string digestAsString()
		{
			std::string s;
			this->digest(s);
			return s;
		}
	};

	CheckGenerator& operator<<(CheckGenerator& g, std::vector<std::uint8_t> const& buffer);
	CheckGenerator& operator<<(CheckGenerator& g, std::string const& s);
	CheckGenerator& operator<<(CheckGenerator& g, std::istream& in);
	CheckGenerator& operator>>(CheckGenerator& g, std::vector<std::uint8_t>& buffer);
	CheckGenerator& operator>>(CheckGenerator& g, std::string& s);
	CheckGenerator& operator>>(CheckGenerator& g, std::ostream& in);
}

#endif /* _GDCRYPTO_CHECKGENERATOR_HPP */