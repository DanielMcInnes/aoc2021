cmake_minimum_required(VERSION 3.5)

project(24a LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(24a
    grid.h grid.cpp
    location.h location.cpp
    blizzard.h blizzard.cpp
    xy.h xy.cpp
    directions.h
    main.cpp)

install(TARGETS 24a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
