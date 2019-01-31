cmake_minimum_required(VERSION 3.5)
project(appUpdater)

include_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/include")
link_directories("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib")

configure_file("${PROJECT_SOURCE_DIR}/version_template.h" "${PROJECT_SOURCE_DIR}/version.h")

set(SRC_LIST updater.cpp)

add_library(${PROJECT_NAME}Static STATIC ${SRC_LIST})
add_library(${PROJECT_NAME}Shared SHARED ${SRC_LIST})

target_link_libraries(${PROJECT_NAME}Shared "curldll")

configure_file("${PROJECT_SOURCE_DIR}/../3d-party/curl/lib/libcurl.dll" ${PROJECT_BINARY_DIR} COPYONLY)
