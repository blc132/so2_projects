cmake_minimum_required(VERSION 3.13)
project(01_balls)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-lncurses -pthread")
SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
add_executable(01_balls main.cpp src/Ball.cpp include/Ball.h enums/direction.h enums/speed.h)