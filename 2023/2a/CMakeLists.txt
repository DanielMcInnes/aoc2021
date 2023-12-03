cmake_minimum_required(VERSION 3.5)

project(2a LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(2a main.cpp)

install(TARGETS 2a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
