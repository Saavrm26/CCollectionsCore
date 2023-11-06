cmake_minimum_required(VERSION 3.5)

project("CCollectionCore_tests")

add_executable(vector_tests "vector_tests.cpp")

target_link_libraries(vector_tests PUBLIC GTest::gtest_main "CCollectionCore")

include(GoogleTest)
gtest_discover_tests(vector_tests)
