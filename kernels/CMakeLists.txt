cmake_minimum_required(VERSION 3.5)

project(mnnl)

############################################################
# Create a library
############################################################

file(GLOB_RECURSE MNNL_SOURCE_FILES src/*/*.cpp)

#Generate the static library from the library sources
add_library(mnnl STATIC
  ${MNNL_SOURCE_FILES}
)

target_include_directories(mnnl
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)


############################################################
# Create an executable
############################################################

# Add an executable with the above sources
#add_executable(hello_binary
#    half_test.cpp
#)
#
## link the new mnnl target with the hello_binary target
#target_link_libraries( hello_binary
#    PRIVATE
#        mnnl
#)
