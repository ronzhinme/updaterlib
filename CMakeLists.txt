cmake_minimum_required(VERSION 3.5)

set (APPUPDATER_VERSION_MAJOR 0)
set (APPUPDATER_VERSION_MINOR 0)

add_subdirectory("src")

if(BUILD_TESTING)
    add_subdirectory("unittests")
endif()