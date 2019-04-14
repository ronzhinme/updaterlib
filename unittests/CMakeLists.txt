cmake_minimum_required(VERSION 2.8)
project(curlCheck)

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")

set(CURL_LIB_PATH "${PROJECT_SOURCE_DIR}/../3d-party/curl")

if (WIN32)
set(SSL_LIB_PATH $ENV{SSL_PATH})
set(CURL_PREFIX "builds/libcurl-vc-x86-release-dll-ssl-dll-ipv6-sspi")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/lib")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}/bin")
link_directories("${SSL_LIB_PATH}/Lib")

elseif(UNIX)
set(CURL_PREFIX "lib/.libs")
link_directories("${CURL_LIB_PATH}/${CURL_PREFIX}")
endif()

add_executable(${PROJECT_NAME}_checkUrl checkUrl.cpp)
add_executable(${PROJECT_NAME}_checkFtp checkFtp.cpp)
add_executable(${PROJECT_NAME}_http-post http-post.c)
add_executable(${PROJECT_NAME}_https-get https.c)
add_executable(${PROJECT_NAME}_checkVersionInfo checkVersionInfo.cpp)
add_executable(${PROJECT_NAME}_checkUpdater checkUpdater.cpp)


set(LIBNAME "curl")
if(WIN32)
set(LIBNAME "libcurl.dll")
endif()

if(WIN32)
configure_file("${CURL_LIB_PATH}/${CURL_PREFIX}/bin/libcurl.dll" "${PROJECT_BINARY_DIR}/Release" COPYONLY)
configure_file("${SSL_LIB_PATH}/libcrypto-1_1.dll" "${PROJECT_BINARY_DIR}/Release" COPYONLY)
configure_file("${SSL_LIB_PATH}/libssl-1_1.dll" "${PROJECT_BINARY_DIR}/Release" COPYONLY)
# elseif(UNIX)
# configure_file("../3d-party/curl/lib/.libs/libcurl.so.4.5.0" ${PROJECT_BINARY_DIR} COPYONLY)
endif()

target_link_libraries(${PROJECT_NAME}_checkUrl ${LIBNAME} "libssl.dll" "libcrypto.dll")
target_link_libraries(${PROJECT_NAME}_checkFtp ${LIBNAME} "libssl.dll" "libcrypto.dll")
target_link_libraries(${PROJECT_NAME}_http-post ${LIBNAME} "libssl.dll" "libcrypto.dll")
target_link_libraries(${PROJECT_NAME}_https-get ${LIBNAME} "libssl.dll" "libcrypto.dll")
target_link_libraries(${PROJECT_NAME}_checkVersionInfo "appUpdaterStatic")
target_link_libraries(${PROJECT_NAME}_checkUpdater "appUpdaterStatic")
target_link_libraries(${PROJECT_NAME}_checkUpdater ${LIBNAME} "libssl.dll" "libcrypto.dll")

add_test(checkUrl ${PROJECT_NAME}_checkUrl)
add_test(checkFtp ${PROJECT_NAME}_checkFtp)
add_test(http-post ${PROJECT_NAME}_http-post)
add_test(https-get ${PROJECT_NAME}_https-get)
add_test(checkVersionInfo ${PROJECT_NAME}_checkVersionInfo)
add_test(checkUpdater ${PROJECT_NAME}_checkUpdater)
