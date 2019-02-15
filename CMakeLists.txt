cmake_minimum_required(VERSION 2.8)
include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 11)
set (APPUPDATER_VERSION_MAJOR 0)
set (APPUPDATER_VERSION_MINOR 0)

add_compile_options(-std=c++11)

add_subdirectory("src")

if(BUILD_TESTING)
    add_subdirectory("unittests")
endif()