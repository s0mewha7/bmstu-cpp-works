cmake_minimum_required(VERSION 3.14)
project(bmstu-works)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG        release-1.12.0
)
FetchContent_MakeAvailable(googletest)
set(CMAKE_CXX_STANDARD 23)
set(TEST_NAME ${PROJECT_NAME}_tests)
add_executable(${TEST_NAME} dummy_string/basic_string.h dummy_string/string_test.cpp let2-dec2oct/dec2oct_test.cpp let2-dec2oct/fromdec2oct.h
let4-struct/struct-to-XML.h let4-struct/xml_format_test.cpp let4-struct/struct.h let5-JacquesFresco/bruteforce.cpp let5-JacquesFresco/function.h)
target_link_libraries(${TEST_NAME} gtest_main)
enable_testing()
include(GoogleTest)
gtest_discover_tests(${TEST_NAME})