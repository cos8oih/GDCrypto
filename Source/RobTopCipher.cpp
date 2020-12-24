#include "External/Base64.hpp"

#include "CAPI.hpp"

#include "GDCrypto/RobTopCipher.hpp"

using namespace gdcrypto;

//RobTopCipher

std::string RobTopCipher::encode(std::vector<uint8_t> const& buffer) const
{
	base64::Base64 b64(base64::URL_SAFE_DICT);
	auto buf = buffer;

	xorWithKey(buf, m_Key);
	return b64.encode(buf);
}

std::string RobTopCipher::encode(std::string const& s) const
{
	return encode(std::vector<uint8_t>(s.begin(), s.end()));
}

std::string RobTopCipher::encode(std::istream& in) const
{
	return encode(std::vector<uint8_t>(std::istreambuf_iterator(in), {}));
}

std::vector<uint8_t> RobTopCipher::decode(std::vector<uint8_t> const& buffer) const
{
	base64::Base64 b64(base64::URL_SAFE_DICT);

	auto buf = b64.decode(buffer);
	xorWithKey(buf, m_Key);

	return buf;
}

std::vector<uint8_t> RobTopCipher::decode(std::string const& s) const
{
	return decode(std::vector<uint8_t>(s.begin(), s.end()));
}

std::vector<uint8_t> RobTopCipher::decode(std::istream& in) const
{
	return decode(std::vector<uint8_t>(std::istreambuf_iterator(in), {}));
}

//C Bindings

inline RobTopCipher* getCipher(void* p) { return reinterpret_cast<RobTopCipher*>(p); }

extern "C"
{
	GDCRYPTO_API void* RobTopCipher_create(
		uint8_t const* key,
		size_t const keySize)
	{
		if (key && keySize)
		{
			return reinterpret_cast<void*>(
				new RobTopCipher(
					std::vector<uint8_t>(key, key + keySize)));
		}

		return nullptr;
	}

	GDCRYPTO_API int RobTopCipher_destroy(void* cipher)
	{
		if (cipher)
		{
			delete getCipher(cipher);
			return GDCRYPTO_SUCCESS;
		}

		return GDCRYPTO_FAIL;
	}

	GDCRYPTO_API uint8_t * RobTopCipher_encode(
		void* cipher,
		uint8_t const* data,
		size_t const dataSize,
		size_t * dataOut)
	{
		if (cipher && data && dataSize)
		{
			std::vector<uint8_t> buffer(data, data + dataSize);
			auto s = getCipher(cipher)->encode(buffer);

			if (s.size())
			{
				if (dataOut)
					*dataOut = s.size();

				return gdcrypto_createBuffer(s.c_str(), s.size());
			}
		}

		return nullptr;
	}

	GDCRYPTO_API uint8_t * RobTopCipher_decode(
		void* cipher,
		uint8_t const* data,
		size_t const dataSize,
		size_t * dataOut)
	{
		if (cipher && data && dataSize)
		{
			std::vector<uint8_t> buffer(data, data + dataSize);
			auto buf = getCipher(cipher)->decode(buffer);

			if (buf.size())
			{
				if (dataOut)
					*dataOut = buf.size();

				return gdcrypto_createBuffer(buf.data(), buf.size());
			}
		}

		return nullptr;
	}
}