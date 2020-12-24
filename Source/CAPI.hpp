#ifndef _GDCRYPTO_CAPI_HPP
#define _GDCRYPTO_CAPI_HPP

#include "GDCrypto/Export.hpp"

#include <cstdint>
#include <cstring>

#define GDCRYPTO_SUCCESS	0
#define GDCRYPTO_FAIL		1

extern "C"
{
	GDCRYPTO_API uint8_t* gdcrypto_allocateBuffer(size_t const size);

	GDCRYPTO_API int gdcrypto_freeBuffer(uint8_t* buffer);

	GDCRYPTO_API uint8_t* gdcrypto_createBuffer(
		void const* data,
		size_t const size);
}

#endif /* _GDCRYPTO_CAPI_HPP */