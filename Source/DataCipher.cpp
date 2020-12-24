#define CBC 0
#define CTR 0

#include "External/Base64.hpp"

#include "CAPI.hpp"
#include "AES.hpp"
#include "ZlibHelper.hpp"

#include "GDCrypto/DataCipher.hpp"

using namespace gdcrypto;

//Globals

static std::array<std::uint8_t, 32u> const IOS_KEY =
{
	0x69, 0x70, 0x75, 0x39, 0x54, 0x55, 0x76, 0x35,
	0x34, 0x79, 0x76, 0x5D, 0x69, 0x73, 0x46, 0x4D,
	0x68, 0x35, 0x40, 0x3B, 0x74, 0x2E, 0x35, 0x77,
	0x33, 0x34, 0x45, 0x32, 0x52, 0x79, 0x40, 0x7B,
};

//Helpers

inline void doPKCS7(std::vector<std::uint8_t>& buffer)
{
	std::uint8_t missing = (buffer.size() % AES_BLOCKLEN);

	if (missing)
	{
		missing = AES_BLOCKLEN - missing;

		for (auto i = 0u; i < missing; ++i)
			buffer.push_back(missing);
	}
}

inline void removePKCS7(std::vector<std::uint8_t>& buffer)
{
	auto padEnd = buffer.back();

	if (padEnd < AES_BLOCKLEN)
	{
		auto it = (buffer.end() - padEnd);

		while (it != buffer.end())
		{
			if (*(it++) != padEnd)
				return;
		}

		buffer.erase(
			it - padEnd,
			buffer.end());
	}
}

std::vector<std::uint8_t> ecbEncryptWithKey(
	std::vector<std::uint8_t> const& buffer,
	std::vector<std::uint8_t> const& key)
{
	if (buffer.size() &&
		key.size() == AES_KEYLEN)
	{
		AES_ctx ctx = {};
		std::vector<std::uint8_t> out(buffer);

		AES_init_ctx(&ctx, key.data());

		doPKCS7(out);

		for (auto i = 0u;
			i < out.size();
			i += AES_BLOCKLEN)
			AES_ECB_encrypt(&ctx, out.data() + i);

		return out;
	}

	return {};
}

std::vector<std::uint8_t> ecbDecryptWithKey(
	std::vector<std::uint8_t> const& buffer,
	std::vector<std::uint8_t> const& key)
{
	if (!(buffer.size() % AES_BLOCKLEN) &&
		key.size() == AES_KEYLEN)
	{
		AES_ctx ctx = {};
		std::vector<std::uint8_t> out(buffer);

		AES_init_ctx(&ctx, key.data());

		for (auto i = 0u;
			i < buffer.size();
			i += AES_BLOCKLEN)
			AES_ECB_decrypt(&ctx, out.data() + i);

		removePKCS7(out);

		return out;
	}

	return {};
}

//DataCipher

std::string DataCipher::encode(std::vector<std::uint8_t> const& buffer) const
{
	std::string s;
	base64::Base64 b64(base64::URL_SAFE_DICT);

	s = m_AES
		? gdcrypto::toString(
			ecbEncryptWithKey(
				buffer,
				gdcrypto::vecFromArray(IOS_KEY)))
		: b64.encode(zlib::deflateBuffer(buffer));

	xorWithKey(s, m_Key);

	return s;
}

std::string DataCipher::encode(std::string const& s) const
{
	return encode(std::vector<std::uint8_t>(s.begin(), s.end()));
}

std::string DataCipher::encode(std::istream& in) const
{
	return encode(std::vector<std::uint8_t>(std::istreambuf_iterator(in), {}));
}

std::vector<std::uint8_t> DataCipher::decode(std::vector<std::uint8_t> const& buffer) const
{
	base64::Base64 b64(base64::URL_SAFE_DICT);

	auto buf = buffer;

	xorWithKey(buf, m_Key);

	if (m_AES)
	{
		return ecbDecryptWithKey(
			buf,
			gdcrypto::vecFromArray(IOS_KEY));
	}

	buf = b64.decode(buf);
	return zlib::inflateBuffer(buf);
}

std::vector<std::uint8_t> DataCipher::decode(std::string const& s) const
{
	return decode(std::vector<std::uint8_t>(s.begin(), s.end()));
}

std::vector<std::uint8_t> DataCipher::decode(std::istream& in) const
{
	return decode(std::vector<std::uint8_t>(std::istreambuf_iterator(in), {}));
}

//C Bindings

inline DataCipher* getCipher(void* p) { return reinterpret_cast<DataCipher*>(p); }

extern "C"
{
	GDCRYPTO_API void* DataCipher_create(
		int const aes,
		std::uint8_t const* key,
		size_t const keySize)
	{
		if (key && keySize)
		{
			return reinterpret_cast<void*>(
				new DataCipher(
					aes,
					std::vector<std::uint8_t>(key, key + keySize)));
		}

		return nullptr;
	}

	GDCRYPTO_API int DataCipher_destroy(void* cipher)
	{
		if (cipher)
		{
			delete getCipher(cipher);
			return GDCRYPTO_SUCCESS;
		}

		return GDCRYPTO_FAIL;
	}

	GDCRYPTO_API std::uint8_t* DataCipher_encode(
		void* cipher,
		std::uint8_t const* data,
		size_t const dataSize,
		size_t* dataOut)
	{
		if (cipher && data && dataSize)
		{
			std::vector<std::uint8_t> buffer(data, data + dataSize);
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

	GDCRYPTO_API std::uint8_t* DataCipher_decode(
		void* cipher,
		std::uint8_t const* data,
		size_t const dataSize,
		size_t* dataOut)
	{
		if (cipher && data && dataSize)
		{
			std::vector<std::uint8_t> buffer(data, data + dataSize);
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