cmake_minimum_required(VERSION 3.20 FATAL_ERROR)
project(ControlSystemTools LANGUAGES CXX)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
# -Wdouble-promotion -Wfloat-conversion -fsingle-precision-constant

add_subdirectory(external)
add_subdirectory(lib)
add_subdirectory(test)