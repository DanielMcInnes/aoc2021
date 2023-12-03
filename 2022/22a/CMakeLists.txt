cmake_minimum_required(VERSION 3.5)

project(22a LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(22a
    directions.h directions.cpp
    xy.h
    map2d.h
    map22a.h
    main.cpp)

install(TARGETS 22a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
