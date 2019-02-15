cmake_minimum_required(VERSION 2.8)
include(CTest)
enable_testing()

set (APPUPDATER_VERSION_MAJOR 0)
set (APPUPDATER_VERSION_MINOR 0)
set (APPUPDATER_VERSION_RELEASE 0)
set (APPUPDATER_VERSION_BUILD 1)

add_compile_options(-std=c++11)

add_subdirectory("src")

if(BUILD_TESTING)
    add_subdirectory("unittests")
endif()