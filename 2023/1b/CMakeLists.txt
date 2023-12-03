cmake_minimum_required(VERSION 3.14)

project(1b LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(1b
  main.cpp
)
