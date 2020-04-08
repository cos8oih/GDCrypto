#ifndef _GDCRYPTO_BASE64_HPP
#define _GDCRYPTO_BASE64_HPP

#include <vector>
#include <string>
#include <stdexcept>

namespace gdcrypto::base64
{
	static std::string const DICT =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

	static std::string const URL_SAFE_DICT =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-_";

	static const auto PAD = '=';
	static const auto NO_PAD = '\0';

	static const auto TABLE_SIZE = 256u;

	class Base64
	{
		std::string m_sDict;
		char m_cPad;
		std::vector<uint8_t> m_vTable;

		void buildTable()
		{
			for (auto i = 0u; i < TABLE_SIZE; ++i)
			{
				auto pos = m_sDict.find(static_cast<char>(i));
				m_vTable.push_back(pos != std::string::npos
					? static_cast<uint8_t>(pos) : '\0');
			}
		}

		bool hasPadding(std::string const& buffer) const
		{
			return buffer.size() &&
				(buffer.size() % 4 ||
					buffer.back() == m_cPad);
		}

		size_t getDecodedSize(std::string const& buffer) const
		{
			return ((buffer.size() + 3) / 4 - hasPadding(buffer)) * 4;
		}
	public:
		Base64(
			std::string const& dict = base64::DICT,
			char const pad = base64::PAD)
			: m_sDict(dict),
			m_cPad(pad)
		{
			if (dict.size() != 64)
				throw std::runtime_error("Size of dictionary must be 64.");

			buildTable();
		}

		Base64(char const pad)
			: m_sDict(base64::DICT),
			m_cPad(pad)
		{
			buildTable();
		}

		//Algorithms

		std::string encode(std::vector<uint8_t> const& buffer) const
		{
			std::string out;

			auto it = buffer.begin();
			auto end = buffer.end();

			for (it;
				std::distance(it, end) >= 3;
				it += 3)
			{
				out.push_back(m_sDict[it[0] >> 2]);
				out.push_back(m_sDict[((it[0] & 0x03) << 4) | (it[1] >> 4)]);
				out.push_back(m_sDict[((it[1] & 0x0f) << 2) | (it[2] >> 6)]);
				out.push_back(m_sDict[it[2] & 0x3f]);
			}

			if (m_cPad != base64::NO_PAD &&
				std::distance(it, end))
			{
				out.push_back(m_sDict[it[0] >> 2]);

				if (std::distance(it, end) == 1)
				{
					out.push_back(m_sDict[(it[0] & 0x03) << 4]);
					out.push_back(m_cPad);
				}
				else
				{
					out.push_back(m_sDict[((it[0] & 0x03) << 4) | (it[1] >> 4)]);
					out.push_back(m_sDict[(it[1] & 0x0f) << 2]);
				}

				out.push_back(m_cPad);
			}

			return out;
		}

		std::vector<uint8_t> decode(std::string const& buffer) const
		{
			std::vector<uint8_t> out;

			auto const outSize = getDecodedSize(buffer);

			for (auto i = 0u; i < outSize; i += 4)
			{
				auto const n =
					m_vTable[buffer[i]] << 18 |
					m_vTable[buffer[i + 1]] << 12 |
					m_vTable[buffer[i + 2]] << 6 |
					m_vTable[buffer[i + 3]];

				out.push_back(n >> 16);
				out.push_back((n >> 8) & 0xFF);
				out.push_back(n & 0xFF);
			}

			if (hasPadding(buffer))
			{
				auto n = m_vTable[buffer[outSize]] << 18 |
					m_vTable[buffer[outSize + 1]] << 12;

				out.push_back(n >> 16);

				if (buffer.size() > (outSize + 2) &&
					buffer[outSize + 2] != m_cPad)
				{
					n |= m_vTable[buffer[outSize + 2]] << 6;
					out.push_back((n >> 8) & 0xFF);
				}
			}

			return out;
		}

		//Overloads

		template <typename It>
		std::string encode(It const& begin, It const& end) const
		{
			return encode(std::vector<uint8_t>(begin, end));
		}

		std::string encode(std::string const& buffer) const
		{
			return encode(buffer.begin(), buffer.end());
		}

		template <typename It>
		std::vector<uint8_t> decode(It const& begin, It const& end) const
		{
			return decode(std::string(begin, end));
		}

		std::vector<uint8_t> decode(std::vector<uint8_t> const& buffer) const
		{
			return decode(buffer.begin(), buffer.end());
		}
	};
}	

#endif /* _GDCRYPTO_BASE64_HPP */