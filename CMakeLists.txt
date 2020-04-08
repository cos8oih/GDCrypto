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

#Define libraries
ADD_LIBRARY(gdcrypto SHARED ${GDCRYPTO_SRC})
ADD_LIBRARY(gdcrypto-static STATIC ${GDCRYPTO_SRC})

#Link libraries
if (DEFINED ZLIB_PATH)
    TARGET_LINK_LIBRARIES(gdcrypto ${ZLIB_PATH})
    TARGET_LINK_LIBRARIES(gdcrypto-static ${ZLIB_PATH})
else()
    MESSAGE(FATAL_ERROR "Zlib path not set!!!")
endif()

#Define tests
ADD_EXECUTABLE(ciphertest "./Tests/CipherTest.cpp")
TARGET_LINK_LIBRARIES(ciphertest gdcrypto-static)

ADD_EXECUTABLE(datatest "./Tests/DataTest.cpp")
TARGET_LINK_LIBRARIES(datatest gdcrypto-static)

ADD_EXECUTABLE(checktest "./Tests/CheckTest.cpp")
TARGET_LINK_LIBRARIES(checktest gdcrypto-static)