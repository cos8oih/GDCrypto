# GDCrypto
C++ library that implements all Geometry Dash algorithms.
## Todo
* Update cmake file
* More tests (both code and bindings)
* XML prettify utility?
* Single header file utility?
## How-to
Header files are fully documented; moreover, the [Examples](Examples) folder contains some examples.
## Building (not working)
CMake is required: clone this repo, then open the cmd and type:
```
mkdir Build
cd Build
cmake .. -DZLIB_PATH=PATH/TO/ZLIB
```
Both static and shared library projects will be built.
## Credits
GDCrypto uses [AES](https://github.com/kokke/tiny-AES-c), [Zlib](https://github.com/madler/zlib), [SHA1](https://github.com/vog/sha1), and Base64:
* [Jouni Malinen's base64 encoder](http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c)
* [Polfosol's base64 decoder](https://stackoverflow.com/a/37109258)

A huge thanks to [Absolute](https://github.com/absoIute) and [MgostIH](https://github.com/mgostIH), who helped me studying the iOS savefile algorithm.