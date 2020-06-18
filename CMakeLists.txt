CMAKE_MINIMUM_REQUIRED(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GDCrypto)

#Options
option(GDCRYPTO_STATIC "Compile GDCrypto as a static library" OFF)
option(GDCRYPTO_EXAMPLES "Includes examples from compilation" OFF)

# Include directories
INCLUDE_DIRECTORIES(.)

#Source files
set (GDCRYPTO_SRC
    ../Source/AES.c
    ../Source/ZlibHelper.cpp
    ../Source/SHA1.cpp
    ../Source/CAPI.cpp
    ../Source/RobTopCipher.cpp
    ../Source/DataCipher.cpp
    ../Source/CheckGenerator.cpp
    ../Source/Utility.cpp
)

#Define libraries
if (GDCRYPTO_STATIC)
    ADD_LIBRARY(GDCrypto STATIC ${GDCRYPTO_SRC})
else()
    ADD_LIBRARY(GDCrypto SHARED ${GDCRYPTO_SRC})
endif()

#Link zlib
if (DEFINED ZLIB_PATH)
    TARGET_LINK_LIBRARIES(GDCrypto ${ZLIB_PATH})
else()
    MESSAGE(FATAL_ERROR "Zlib path not set.")
endif()

#Define examples
if (GDCRYPTO_EXAMPLES)
    ADD_EXECUTABLE(GJPTool "../Examples/CipherExample.cpp")
    TARGET_LINK_LIBRARIES(GJPTool GDCrypto)

    ADD_EXECUTABLE(SavegameTool "../Examples/DataExample.cpp")
    TARGET_LINK_LIBRARIES(SavegameTool GDCrypto)

    #ADD_EXECUTABLE(checktest "./Tests/CheckTest.cpp")
    #TARGET_LINK_LIBRARIES(checktest gdcrypto-static)

endif()