project(appUpdater)

configure_file("${PROJECT_SOURCE_DIR}/version_template.h" "${PROJECT_SOURCE_DIR}/version.h")

find_package(pugixml REQUIRED)
find_package(CURL REQUIRED) 
find_package(OpenSSL REQUIRED) 

include_directories(${pugixml_INCLUDE_DIRS})
include_directories(${CURL_INCLUDE_DIRS})
include_directories(${OpenSSL_INCLUDE_DIRS})

set(SRC_LIST updater.h updater.cpp 
             versionInfo.h versionInfo.cpp 
             curlBridge.h curlBridge.cpp 
             xmlParser.h xmlParser.cpp 
             platformSpecific.h platformSpecific.cpp)

add_library(${PROJECT_NAME}Static STATIC ${SRC_LIST})
add_library(${PROJECT_NAME}Shared SHARED ${SRC_LIST} updaterInterface.h updaterInterface.cpp)

set_property(TARGET ${PROJECT_NAME}Shared PROPERTY POSITION_INDEPENDENT_CODE ON)
target_link_libraries(${PROJECT_NAME}Shared pugixml::pugixml CURL::libcurl OpenSSL::Crypto OpenSSL::SSL)