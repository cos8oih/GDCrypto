#ifndef _GDCRYPTO_EXPORT_HPP
#define _GDCRYPTO_EXPORT_HPP

#if defined(GDCRYPTO_BUILD)
	#if not defined(GDCRYPTO_STATIC)
		#if defined(_MSC_VER)
			#define GDCRYPTO_API __declspec(dllexport)
		#else
			#define GDCRYPTO_API __attribute__((visibility("default")))
		#endif
	#endif
#else
	#define GDCRYPTO_API
#endif

#endif /* _GDCRYPTO_EXPORT_HPP */