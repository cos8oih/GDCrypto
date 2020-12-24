#include "CAPI.hpp"

extern "C"
{
	GDCRYPTO_API uint8_t* gdcrypto_allocateBuffer(size_t const size)
	{
		return new uint8_t[size];
	}

	GDCRYPTO_API int gdcrypto_freeBuffer(uint8_t* buffer)
	{
		if (buffer)
		{
			delete[] buffer;
			return GDCRYPTO_SUCCESS;
		}

		return GDCRYPTO_FAIL;
	}

	//This is probably broken (null byte missing)
	GDCRYPTO_API uint8_t* gdcrypto_createBuffer(
		void const* data,
		size_t const size)
	{
		if (data && size)
		{
			auto p = gdcrypto_allocateBuffer(size);

			if (p)
				memcpy(p, data, size);

			return p;
		}

		return nullptr;
	}
}