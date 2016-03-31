project(test)
include_directories(gtest gtest/include)
set(SRC_GTEST BinaryTree_test.cpp gtest/src/gtest_main.cc gtest/src/gtest-all.cc)
add_executable(gtest ${SRC_GTEST})