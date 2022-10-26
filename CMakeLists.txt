cmake_minimum_required(VERSION 3.23)
project(assassins_v2)

set(CMAKE_CXX_STANDARD 17)

add_executable(assassins_v2 main.cpp include/Player.h include/Container.h include/Log.h src/Player.cpp src/Container.cpp src/Log.cpp)
