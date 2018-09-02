# GDCrypto
C++ library to encode/decode GD stuff
## Todo
* Add the ability to encode savegames for the sake of completion.
* C bindings.
* Add a Makefile.
## How-to
Just look at the examples or read the header, too lazy to write here.
## Compiling
GDCrypto was built on Visual Studio 2017, so other compilers aren't tested. To compile it, yo'll need zlib.
## Credits
The `Base64_Encode()` function is based on the function made by Jouni Malinen, while `Base64_Decode()` is based on the function made by Polfosol. You can find both versions here:

* [Jouni Malinen's base64 implementation](http://web.mit.edu/freebsd/head/contrib/wpa/src/utils/base64.c)
* [Polfosol's base64 implementation](https://stackoverflow.com/a/37109258)

 I'd also like to thanks [Absolute](https://github.com/absoIute), who gave me an example code of how to use Inflate(), and [MgostIH](https://github.com/mgostIH), who gave me some tips on how to optimize the code.
