cmake_minimum_required(VERSION 2.8)
include(CTest)
enable_testing()

set (APPUPDATER_VERSION_MAJOR 0)
set (APPUPDATER_VERSION_MINOR 0)
set (APPUPDATER_VERSION_RELEASE 0)
set (APPUPDATER_VERSION_BUILD 1)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if (WIN32)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 bits
        set(SSL_LIB_PATH "C:/Program Files/OpenSSL-Win64")
        set(CURL_PREFIX "builds/libcurl-vc-x64-release-dll-ssl-dll-ipv6-sspi")
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4) # 32 bits
        set(SSL_LIB_PATH "C:/Program Files (x86)/OpenSSL-Win32")
        set(CURL_PREFIX "builds/libcurl-vc-x86-release-dll-ssl-dll-ipv6-sspi")
    endif()
endif()

add_subdirectory("src")

if(BUILD_TESTING)
    add_subdirectory("unittests")
endif()