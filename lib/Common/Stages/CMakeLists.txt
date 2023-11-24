add_library(StageHandler)

set_target_properties(StageHandler PROPERTIES LINKER_LANGUAGE CXX)

target_sources(StageHandler
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/Stage.hpp
        ${CMAKE_CURRENT_LIST_DIR}/StageHandler.hpp
)

target_link_libraries(StageHandler
        PUBLIC
        Time
)

target_include_directories(StageHandler
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
