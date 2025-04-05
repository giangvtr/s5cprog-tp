cmake_minimum_required(VERSION 3.20)
project(player-multimedia C)

set(CMAKE_C_STANDARD 90)

add_executable(testMO main_testMO.c multimedia-object.c test.c)
