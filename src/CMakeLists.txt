add_library(Vec3 Vec3.hpp)
add_library(Quaternion Quaternion.hpp)

set_target_properties(Vec3 PROPERTIES LINKER_LANGUAGE CXX)
set_target_properties(Quaternion PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(Vec3 PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_include_directories(Quaternion PUBLIC ${CMAKE_CURRENT_LIST_DIR})