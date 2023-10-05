add_library(Container Container.hpp)
add_library(Vec3 Vec3.hpp)

set_target_properties(Container PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Vec3 PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Container PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Vec3 PUBLIC ${CMAKE_CURRENT_LIST_DIR})