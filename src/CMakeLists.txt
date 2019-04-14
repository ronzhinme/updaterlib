cmake_minimum_required(VERSION 2.8)
project(appUpdater)

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")
include_directories("${PROJECT_SOURCE_DIR}/../3d-party/libxml2/include")

set(CURL_LIB_PATH "${PROJECT_SOURCE_DIR}/../3d-party/curl")
set(LIBXML2_LIB_PATH "${PROJECT_SOURCE_DIR}/../3d-party/libxml2")

if (WIN32)
set(SSL_LIB_PATH $ENV{SSL_PATH})
set(CURL_PREFIX "builds/libcurl-vc-x86-release-dll-ssl-dll-ipv6-sspi")
set(LIBXML2_PREFIX "win32/bin.msvc")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/lib")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/bin")
link_directories("${LIBXML2_LIB_PATH}/${LIBXML2_PREFIX}")
link_directories("${SSL_LIB_PATH}/Lib")

elseif(UNIX)
set(CURL_PREFIX "lib/.libs")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}")
endif()

configure_file("${PROJECT_SOURCE_DIR}/version_template.h" "${PROJECT_SOURCE_DIR}/version.h")

set(SRC_LIST  updater.h updater.cpp 
              versionInfo.h versionInfo.cpp 
              curlBridge.h curlBridge.cpp)

add_library(${PROJECT_NAME}Static STATIC ${SRC_LIST})
add_library(${PROJECT_NAME}Shared SHARED ${SRC_LIST})

if (WIN32)
target_link_libraries(${PROJECT_NAME}Shared "libcurl.dll" "libxml2.dll" "libcrypto.dll" "libssl.dll")

elseif(UNIX)
target_link_libraries(${PROJECT_NAME}Shared "curl")
configure_file("${CURL_LIB_PATH}/lib/.libs/libcurl.so.4.5.0" ${PROJECT_BINARY_DIR} COPYONLY)
endif()