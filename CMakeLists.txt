# cmake --version
cmake_minimum_required(VERSION 3.5)

# project name
project(mnnl_project)

# set c++ standard
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(kernels)

add_executable(mnnl_project test/dtype_half_test/half_test.cpp)

target_link_libraries(mnnl_project PRIVATE mnnl)

