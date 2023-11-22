add_library(Time)

set_target_properties(Time PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Time
        PUBLIC
        Time.hpp
        HardwareClock.hpp
        ManualClock.hpp
        Stopwatch.hpp
)

target_include_directories(Time
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
