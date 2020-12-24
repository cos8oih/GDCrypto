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
#ifndef _GDCRYPTO_ROBTOPCIPHER_HPP
#define _GDCRYPTO_ROBTOPCIPHER_HPP

#include "GDCrypto/Utility.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace gdcrypto
{
	/*
		RobTopCipher

		The RobTop Cipher is a cipher widely used in Geometry Dash. It's the combination
		of the base64 (url safe) algorithm and the bitwise XOR operation, where every
		char of the result string is XORed with a character of the key (array of chars).
		Note: if you dont set a key/set the key to { '\0' }, the cipher will effectively
		act as a Base64 encoder/decoder (see Base64Cipher below).
	*/
	class GDCRYPTO_API RobTopCipher
	{
	protected:
		std::vector<std::uint8_t> m_Key;
	public:
		RobTopCipher(std::vector<std::uint8_t> const& key)
			: m_Key(key) {}

		std::string encode(std::vector<std::uint8_t> const& buffer) const;
		std::string encode(std::string const& s) const;
		std::string encode(std::istream& in) const;

		std::vector<std::uint8_t> decode(std::vector<std::uint8_t> const& buffer) const;
		std::vector<std::uint8_t> decode(std::string const& s) const;
		std::vector<std::uint8_t> decode(std::istream& in) const;
	};

	class Base64Cipher
		: public RobTopCipher
	{
	public:
		Base64Cipher()
			: RobTopCipher(gdcrypto::vecFromArray(keys::NULL_KEY)) {}
	};
}

#endif /* _GDCRYPTO_ROBTOPCIPHER_HPP */