cmake_minimum_required(VERSION 3.14)

project(23a LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set (CMAKE_BUILD_TYPE DEBUG)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(23a
    grid.h
    grid.cpp
    main.cpp
)
#target_link_libraries(23a)

install(TARGETS 23a
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
