enable_testing()

add_executable(Vec3-test ${CMAKE_CURRENT_LIST_DIR}/Vec3-test.cpp)
target_link_libraries(Vec3-test
        PRIVATE
        GTest::gtest_main
        Math
)

add_executable(Quaternion-test ${CMAKE_CURRENT_LIST_DIR}/Quaternion-test.cpp)
target_link_libraries(Quaternion-test
        PRIVATE
        GTest::gtest_main
        Math
)

add_executable(PID-test ${CMAKE_CURRENT_LIST_DIR}/PID-test.cpp)
target_link_libraries(PID-test
        PRIVATE
        GTest::gtest_main
        Control
)

add_executable(LQR-test ${CMAKE_CURRENT_LIST_DIR}/LQR-test.cpp)
target_link_libraries(LQR-test
        PRIVATE
        GTest::gtest_main
        Control
)

add_executable(KF-test ${CMAKE_CURRENT_LIST_DIR}/KF-test.cpp)
target_link_libraries(KF-test
        PRIVATE
        GTest::gtest_main
        Estimate
)

add_executable(Time-test ${CMAKE_CURRENT_LIST_DIR}/Time-test.cpp)
target_link_libraries(Time-test
        PRIVATE
        GTest::gtest_main
        Time
)

add_executable(Random-test ${CMAKE_CURRENT_LIST_DIR}/Random-test.cpp)
target_link_libraries(Random-test
        PRIVATE
        GTest::gtest_main
        Random
)

add_executable(StageHandler-test ${CMAKE_CURRENT_LIST_DIR}/StageHandler-test.cpp)
target_link_libraries(StageHandler-test
        PRIVATE
        GTest::gtest_main
        StageHandler
)

add_executable(Simulation-test ${CMAKE_CURRENT_LIST_DIR}/Simulation-test.cpp)
target_link_libraries(Simulation-test
        PRIVATE
        GTest::gtest_main
        Simulation
)

add_executable(StateMachine-test ${CMAKE_CURRENT_LIST_DIR}/StateMachine-test.cpp)
target_link_libraries(StateMachine-test
        PRIVATE
        GTest::gtest_main
        StageHandler
)

include(GoogleTest)
gtest_discover_tests(
        Vec3-test
        Quaternion-test
        PID-test
        LQR-test
        StateMachine-test
)