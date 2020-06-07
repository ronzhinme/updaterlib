cmake_minimum_required(VERSION 2.8)
project(appUpdater)

set(CURL_LIB_PATH "${PROJECT_SOURCE_DIR}/../3d-party/curl")
set(PUGIXML_LIB_PATH "${PROJECT_SOURCE_DIR}/../3d-party/pugixml")

include_directories(${CURL_LIB_PATH}/include)
include_directories(${PUGIXML_LIB_PATH}/src)

if (WIN32)
set(SSL_LIB_PATH $ENV{SSL_PATH})
if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 bits
    set(CURL_PREFIX "builds/libcurl-vc-x64-release-dll-ssl-dll-ipv6-sspi")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4) # 32 bits
    set(CURL_PREFIX "builds/libcurl-vc-x86-release-dll-ssl-dll-ipv6-sspi")
endif()

include_directories(${SSL_LIB_PATH}/include)

link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/lib")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/bin")
link_directories("${SSL_LIB_PATH}/Lib")

elseif(APPLE)
set(SSL_LIB_PATH $ENV{SSL_PATH})
set(CURL_PREFIX "lib/.libs")

include_directories(${SSL_LIB_PATH}/include)

link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}")
link_directories("${SSL_LIB_PATH}/lib")

elseif(UNIX)
set(CURL_PREFIX "lib/.libs")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}")
endif()

configure_file("${PROJECT_SOURCE_DIR}/version_template.h" "${PROJECT_SOURCE_DIR}/version.h")

set(PUGIXML_SRC "${PUGIXML_LIB_PATH}/src/pugixml.hpp" "${PUGIXML_LIB_PATH}/src/pugixml.cpp" "${PUGIXML_LIB_PATH}/src/pugiconfig.hpp")
set(SRC_LIST ${PUGIXML_SRC} 
             updater.h updater.cpp 
             versionInfo.h versionInfo.cpp 
             curlBridge.h curlBridge.cpp 
             xmlParser.h xmlParser.cpp)

add_library(${PROJECT_NAME}Static STATIC ${SRC_LIST})
add_library(${PROJECT_NAME}Shared SHARED ${SRC_LIST} updaterInterface.h updaterInterface.cpp)
set_property(TARGET ${PROJECT_NAME}Shared PROPERTY POSITION_INDEPENDENT_CODE ON)

if (WIN32)
target_link_libraries(${PROJECT_NAME}Shared "libcurl.dll" "libcrypto.dll" "libssl.dll")
configure_file("${CURL_LIB_PATH}/${CURL_PREFIX}/bin/libcurl.dll" ${PROJECT_BINARY_DIR} COPYONLY)
    if(CMAKE_SIZEOF_VOID_P EQUAL 8) # 64 bits
        configure_file("${SSL_LIB_PATH}/libcrypto-1_1-x64.dll" ${PROJECT_BINARY_DIR} COPYONLY)
        configure_file("${SSL_LIB_PATH}/libssl-1_1-x64.dll" ${PROJECT_BINARY_DIR} COPYONLY)
    elseif(CMAKE_SIZEOF_VOID_P EQUAL 4) # 32 bits
        configure_file("${SSL_LIB_PATH}/libcrypto-1_1.dll" ${PROJECT_BINARY_DIR} COPYONLY)
        configure_file("${SSL_LIB_PATH}/libssl-1_1.dll" ${PROJECT_BINARY_DIR} COPYONLY)
    endif()
elseif(UNIX)
target_link_libraries(${PROJECT_NAME}Shared "curl" "crypto" "ssl")
endif()