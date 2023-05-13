cmake_minimum_required(VERSION 3.25)

project(snake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -Wconversion")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_BUILD_TYPE "Release")

include_directories(lib/console-engine/include)

add_executable(snake src/main.cc lib/console-engine/src/console.cc)
