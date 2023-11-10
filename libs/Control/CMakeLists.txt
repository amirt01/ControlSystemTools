add_library(Control)

set_target_properties(Control PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Control
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Controller.hpp
        ${CMAKE_CURRENT_LIST_DIR}/PID.hpp
)

target_include_directories(Control
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
