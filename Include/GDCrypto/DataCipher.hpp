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
#ifndef _GDCRYPTO_DATACIPHER_HPP
#define _GDCRYPTO_DATACIPHER_HPP

#include "GDCrypto/Utility.hpp"

#include <vector>
#include <string>
#include <iostream>

namespace gdcrypto
{
	/*
		DataCipher

		This class is used to encode/decode data, like savegames or level strings.
		The algorithm used is either:
		1) Deflate + base64 (url safe) for encoding, base64 + inflate for decoding;
		2) AES-256 ECB mode with a fixed key.
		A XOR operation can be applied after the algorithm.
	*/
	class GDCRYPTO_API DataCipher
	{
	protected:
		bool m_AES;
		std::vector<std::uint8_t> m_Key;
	public:
		DataCipher(
			bool aes = false,
			std::vector<std::uint8_t> const& key = {})
			: m_AES(aes),
			m_Key(key) {}
		DataCipher(
			std::vector<std::uint8_t> const& key)
			: m_AES(false),
			m_Key(key) {}

		std::string encode(std::vector<std::uint8_t> const& buffer) const;
		std::string encode(std::string const& s) const;
		std::string encode(std::istream& in) const;

		std::vector<std::uint8_t> decode(std::vector<std::uint8_t> const& buffer) const;
		std::vector<std::uint8_t> decode(std::string const& s) const;
		std::vector<std::uint8_t> decode(std::istream& in) const;
	};

	class LevelDataCipher
		: public DataCipher
	{
	public:
		LevelDataCipher()
			: DataCipher(false, gdcrypto::vecFromArray(keys::NULL_KEY)) {}
	};

	class SavegameCipher
		: public DataCipher
	{
	public:
		SavegameCipher()
			: DataCipher(false, gdcrypto::vecFromArray(keys::SAVEGAME_KEY)) {}
	};

	class IOSSavegameCipher
		: public DataCipher
	{
	public:
		IOSSavegameCipher()
			: DataCipher(true, gdcrypto::vecFromArray(keys::NULL_KEY)) {}
	};
}

#endif /* _GDCRYPTO_DATACIPHER_HPP */