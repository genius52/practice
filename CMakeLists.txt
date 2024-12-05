cmake_minimum_required(VERSION 3.7)
project(practice)

set(CMAKE_CXX_STANDARD 11)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(practice ${SOURCES})
