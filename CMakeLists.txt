cmake_minimum_required(VERSION 3.0)
project(ESD)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_SYSTEM_PROCESSOR arm)

#set(CMAKE_SYSROOT ${PROJECT_SOURCE_DIR}/sysroot)
#set(CMAKE_STAGING_PREFIX ${PROJECT_SOURCE_DIR}/stage)

set(tools ${PROJECT_SOURCE_DIR}/tools)
set(CMAKE_C_COMPILER ${tools}/bin/arm-linux-gnueabihf-gcc)
set(CMAKE_CXX_COMPILER ${tools}/bin/arm-linux-gnueabihf-g++)

set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)


#include(${PROJECT_SOURCE_DIR}/cmake/FindGPIO.cmake)

include(cmake/DeploymentTest.cmake)


add_subdirectory(src)
add_subdirectory(app)
add_subdirectory(extern)
