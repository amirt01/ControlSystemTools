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

include(GoogleTest)

add_executable(Vec3-test Vec3-test.cpp)
add_executable(Vector-test Vector-test.cpp)

add_test(NAME Vec3-test COMMAND $<TARGET_FILE:Vec3-test>)
target_link_libraries(Vec3-test PRIVATE GTest::gtest_main Vec3)

add_test(NAME Vector-test COMMAND $<TARGET_FILE:Vector-test>)
target_link_libraries(Vector-test PRIVATE GTest::gtest_main Vector)

gtest_discover_tests(Vec3-test)
gtest_discover_tests(Vector-test)