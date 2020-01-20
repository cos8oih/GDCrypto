# GDCrypto
C++ library that implements common Geometry Dash algorithms.
## Todo
* Fix data encoding algorithm
* Finish C bindings
* Finish writing tests
* Bindings for other languages
* Improve Base64 library
* XML prettify utility
## How-to
The main header file ([GDCrypto.hpp](Include/GDCrypto.hpp)) is fully documented; moreover, the [Tests](Tests) folder contains some examples about the library functionalities.
## Building
CMake is required: clone this repo, then open the cmd and type:
```
mkdir Build
cd Build
cmake .. -DZLIB_PATH=PATH/TO/ZLIB
```
Both static and shared library projects will be built.
## Credits
GDCrypto uses [Zlib](https://github.com/madler/zlib), [SHA1](https://github.com/vog/sha1), and Base64:
* [Jouni Malinen's base64 encoder](http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c)
* [Polfosol's base64 decoder](https://stackoverflow.com/a/37109258)

 I'd also like to thanks [Absolute](https://github.com/absoIute), who helped me with the inflate algorithm, and [MgostIH](https://github.com/mgostIH), who gave me some tips on how to optimize the code.
