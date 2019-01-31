cmake_minimum_required(VERSION 3.5)
project(curlCheck)
include(CTest)
enable_testing()

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib")

add_executable(${PROJECT_NAME}_checkUrl checkUrl.cpp)
add_executable(${PROJECT_NAME}_checkFtp checkFtp.cpp)
add_executable(${PROJECT_NAME}_http-post http-post.c)
add_executable(${PROJECT_NAME}_https-get https.c)

target_link_libraries(${PROJECT_NAME}_checkUrl "curldll")
target_link_libraries(${PROJECT_NAME}_checkFtp "curldll")
target_link_libraries(${PROJECT_NAME}_http-post "curldll")
target_link_libraries(${PROJECT_NAME}_https-get "curldll")

configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/libcurl.dll" ${PROJECT_BINARY_DIR} COPYONLY)

add_test(checkUrl ${PROJECT_NAME}_checkUrl)
add_test(checkFtp ${PROJECT_NAME}_checkFtp)
add_test(http-post ${PROJECT_NAME}_http-post)
add_test(https-get ${PROJECT_NAME}_https-get)