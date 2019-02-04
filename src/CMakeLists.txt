cmake_minimum_required(VERSION 2.8)
project(appUpdater)

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")

if (WIN32)
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib")
elseif(LINUX)
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/.libs")
endif()

configure_file("${PROJECT_SOURCE_DIR}/version_template.h" "${PROJECT_SOURCE_DIR}/version.h")

set(SRC_LIST updater.cpp)

add_library(${PROJECT_NAME}Static STATIC ${SRC_LIST})
add_library(${PROJECT_NAME}Shared SHARED ${SRC_LIST})

if (WIN32)
target_link_libraries(${PROJECT_NAME}Shared "libcurl.dll")
configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/libcurl.dll" ${PROJECT_BINARY_DIR} COPYONLY)
elseif(LINUX)
target_link_libraries(${PROJECT_NAME}Shared "libcurl.so.*")
configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/.libs/libcurl.so.*" ${PROJECT_BINARY_DIR} COPYONLY)
endif()