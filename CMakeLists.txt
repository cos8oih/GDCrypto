CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GDCrypto)

# Include directories
INCLUDE_DIRECTORIES(.)

#Source files
set (GDCRYPTO_SRC
    ../Source/Base64.cpp
    ../Source/Sha1.cpp
    ../Source/GDCrypto.cpp
)

#define libraries
ADD_LIBRARY(gdcrypto SHARED ${GDCRYPTO_SRC})
ADD_LIBRARY(gdcrypto-static STATIC ${GDCRYPTO_SRC})

#Link libraries
if (DEFINED ZLIB_PATH)
    target_link_libraries(gdcrypto ${ZLIB_PATH})
    target_link_libraries(gdcrypto-static ${ZLIB_PATH})
else()
    message(WARNING "Zlib path not set!!!")
endif()