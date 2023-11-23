add_library(Random)

set_target_properties(Random PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Random
        PUBLIC
        Noise.hpp
        NormalNoise.hpp
        UniformNoise.hpp
)

target_link_libraries(Random
        PUBLIC
        Eigen3::Eigen
)

target_include_directories(Random
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
