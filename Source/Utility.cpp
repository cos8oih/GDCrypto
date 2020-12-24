#include "CAPI.hpp"

#include "GDCrypto/Utility.hpp"

using namespace gdcrypto;

//C Bindings

extern "C"
{
	GDCRYPTO_API void gdcrypto_xorWithKey(
		uint8_t* buffer,
		size_t const bufferSize,
		uint8_t const* key,
		size_t const keySize)
	{
		if (buffer && bufferSize &&
			key && keySize)
		{
			if (!(keySize == 1 && key[0] == '\0'))
			{
				for (auto i = 0u; i < bufferSize; ++i)
					buffer[i] ^= key[i % keySize];
			}
		}
	}

	GDCRYPTO_API uint8_t* gdcrypto_levelSeed(
		uint8_t* levelString,
		size_t const levelStringSize,
		size_t* seedOut)
	{
		if (levelString && levelStringSize)
		{
			std::string s(
				reinterpret_cast<char*>(levelString),
				levelStringSize);

			if (seedOut)
				*seedOut = s.size();

			return gdcrypto_createBuffer(s.c_str(), s.size());
		}

		return nullptr;
	}

	GDCRYPTO_API int32_t gdcrypto_levelscoreSeed(
		uint32_t const jumps,
		uint32_t const percentage,
		uint32_t const seconds)
	{
		return levelscoreSeed(jumps, percentage, seconds);
	}
}