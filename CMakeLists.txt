cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_FLAGS -std=c++11)
message("bin path: " ${PROJECT_BINARY_DIR})
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
add_subdirectory(src)

