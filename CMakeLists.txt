cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(ControlSystemTools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -O3")
# -Wpedantic -Wdouble-promotion -Wfloat-conversion -fsingle-precision-constant

add_subdirectory(external)
add_subdirectory(libs)
add_subdirectory(test)