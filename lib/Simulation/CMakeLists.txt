add_library(Simulation)

set_target_properties(Simulation PROPERTIES LINKER_LANGUAGE CXX)

target_sources(Simulation
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/RigidBody.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Shapes.hpp
        ${CMAKE_CURRENT_LIST_DIR}/Forcer.hpp
        ${CMAKE_CURRENT_LIST_DIR}/MotorProp.hpp
        ${CMAKE_CURRENT_LIST_DIR}/VTOL.hpp
)

target_link_libraries(Simulation
        PUBLIC
        Eigen3::Eigen
        Time
        Types
)

target_include_directories(Simulation
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}
)
