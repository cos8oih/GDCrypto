# GDCrypto

C++ library that implements all Geometry Dash algorithms.

## Todo

* Tests
* Bindings
* XML prettify utility?
## How-to

Header files are fully documented; moreover, the [Examples](Examples) folder contains some examples.

## Building

CMake is required for compiling.
```
mkdir Build
cd Build
cmake {OPTIONS} ..
```
To build a static version:
```
-DGDCRYPTO_STATIC=ON
```
To include examples:
```
-DGDCRYPTO_EXAMPLES=ON
```
32-bit Visual Studio:
```
-G "Visual Studio 16 2019" -A Win32 -Thost=x86
```
64-bit Visual Studio:
```
-G "Visual Studio 16 2019" -A x64 -Thost=x64
```

The [merge.py](merge.py) utility may be used to generate a single header file.
## Credits
GDCrypto uses [AES](https://github.com/kokke/tiny-AES-c), [Zlib](https://github.com/madler/zlib), [SHA1](https://github.com/vog/sha1), and Base64:
* [Jouni Malinen's base64 encoder](http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c)
* [Polfosol's base64 decoder](https://stackoverflow.com/a/37109258)

A huge thanks to [Absolute](https://github.com/absoIute) and [MgostIH](https://github.com/mgostIH), who helped me dechipering the iOS savefile algorithm.
