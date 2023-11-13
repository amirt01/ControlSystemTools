add_library(Math)

set_target_properties(Math PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Math
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Vec3.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Quaternion.hpp
)

target_include_directories(Math
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)