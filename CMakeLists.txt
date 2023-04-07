cmake_minimum_required(VERSION 3.1)
project(appUpdater)
include(CTest)
enable_testing()

set (CMAKE_CXX_STANDARD 11)

set (APPUPDATER_VERSION_MAJOR 0)
set (APPUPDATER_VERSION_MINOR 0)
set (APPUPDATER_VERSION_RELEASE 0)
set (APPUPDATER_VERSION_BUILD 1)

add_subdirectory("src")

if(BUILD_TESTING)
    add_subdirectory("unittests")
endif()
