cmake_minimum_required(VERSION 2.8)
project(curlCheck)

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")

if (WIN32)
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib")
elseif(LINUX)
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/.libs")
endif()

add_executable(${PROJECT_NAME}_checkUrl checkUrl.cpp)
add_executable(${PROJECT_NAME}_checkFtp checkFtp.cpp)
add_executable(${PROJECT_NAME}_http-post http-post.c)
add_executable(${PROJECT_NAME}_https-get https.c)

set(LIBNAME "curl")
if(WIN32)
set(LIBNAME "libcurl.dll")
endif()

target_link_libraries(${PROJECT_NAME}_checkUrl ${LIBNAME})
target_link_libraries(${PROJECT_NAME}_checkFtp ${LIBNAME})
target_link_libraries(${PROJECT_NAME}_http-post ${LIBNAME})
target_link_libraries(${PROJECT_NAME}_https-get ${LIBNAME})

if(WIN32)
configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/libcurl.dll" ${PROJECT_BINARY_DIR} COPYONLY)
elseif(LINUX)
configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/.libs/libcurl.so.*" ${PROJECT_BINARY_DIR} COPYONLY)
endif()

add_test(checkUrl ${PROJECT_NAME}_checkUrl)
add_test(checkFtp ${PROJECT_NAME}_checkFtp)
add_test(http-post ${PROJECT_NAME}_http-post)
add_test(https-get ${PROJECT_NAME}_https-get)