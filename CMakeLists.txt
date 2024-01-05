cmake_minimum_required(VERSION 3.27)
project(zengine)

set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

add_executable(zengine
        src/main.cpp
        src/display.cpp
        src/vector.h
        src/vector.cpp
)

target_link_libraries(zengine ${SDL2_LIBRARIES})
