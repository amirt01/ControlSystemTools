add_library(Control)

set_target_properties(Control PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Control
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Controller.hpp
        ${CMAKE_CURRENT_LIST_DIR}/PID.hpp
        ${CMAKE_CURRENT_LIST_DIR}/StateFeedback.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Model.hpp
)

target_link_libraries(Control
        PUBLIC
        Eigen3::Eigen
)

target_include_directories(Control
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
