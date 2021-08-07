# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
cmake_minimum_required(VERSION 3.5)

# Set the project name
project (half_test)

# Set C++ verrsion
set(CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
message(STATUS "optional:-std=c++11")

# Set compilation options
#add_compile_options("-g -w -O3")

# Create a sources variable with a link to all cpp files to compile
set(SOURCES
    ./../../core/dtype/half.cpp
    ./half_test.cpp
)

# Add an executable with the above sources
add_executable(half_test ${SOURCES})

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(half_test
    PRIVATE
        ${PROJECT_SOURCE_DIR}./../../core/dtype/
)
