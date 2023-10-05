cmake_minimum_required(VERSION 3.5 FATAL_ERROR)
project(ControlSystemTools LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wdouble-promotion")

add_subdirectory(src)
add_subdirectory(tests)