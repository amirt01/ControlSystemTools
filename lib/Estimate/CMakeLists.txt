add_library(Estimate)

set_target_properties(Estimate PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Estimate
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/KalmanFilter.hpp
        ${CMAKE_CURRENT_LIST_DIR}/IMUKalmanFilter.hpp
)

target_link_libraries(Estimate
        PUBLIC
        Eigen3::Eigen
)

target_include_directories(Estimate
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
