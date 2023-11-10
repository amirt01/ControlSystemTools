include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
        DOWNLOAD_DIR ${CMAKE_CURRENT_BINARY_DIR}/
        DOWNLOAD_NO_EXTRACT TRUE
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(Vec3-test
        ${CMAKE_CURRENT_LIST_DIR}/Vec3-test.cpp
)
add_executable(Quaternion-test
        ${CMAKE_CURRENT_LIST_DIR}/Quaternion-test.cpp
)
add_executable(PID-test
        ${CMAKE_CURRENT_LIST_DIR}/PID-test.cpp
)

target_link_libraries(Vec3-test
        PRIVATE
        GTest::gtest_main
        Math
)
target_link_libraries(Quaternion-test
        PRIVATE
        GTest::gtest_main
        Math
)
target_link_libraries(PID-test
        PRIVATE
        GTest::gtest_main
        Control
)

include(GoogleTest)
gtest_discover_tests(Vec3-test)
gtest_discover_tests(Quaternion-test)
gtest_discover_tests(PID-test)