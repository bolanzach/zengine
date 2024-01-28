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
        src/mesh.h
        src/triangle.h
        src/mesh.cpp
        src/triangle.cpp
        src/playground.cpp
        src/playground.h
        src/color.h
)

target_link_libraries(zengine ${SDL2_LIBRARIES})
