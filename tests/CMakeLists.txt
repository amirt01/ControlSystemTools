add_executable(Vec3-test Vec3-test.cpp)

add_test(NAME Vec3-test COMMAND $<TARGET_FILE:Vec3-test>)
target_link_libraries(Vec3-test GTest::gtest_main Vec3)

include(GoogleTest)
gtest_discover_tests(Vec3-test)