cmake_minimum_required(VERSION 3.20)
project(main C)

set(CMAKE_C_STANDARD 90)

add_executable(main main.o edgeList.o graphComponents.h vertexList.o graph.o)
target_link_libraries(main m)
