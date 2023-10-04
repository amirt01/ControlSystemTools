add_library(Vec3 "")

set_target_properties(Vec3 PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Vec3 PUBLIC ${CMAKE_CURRENT_LIST_DIR}/Vec3.hpp)
target_include_directories(Vec3 PUBLIC ${CMAKE_CURRENT_LIST_DIR})