add_library(Types)

set_target_properties(Types PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Types
        PUBLIC
        TypeWrapper.hpp
)

target_include_directories(Types
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
