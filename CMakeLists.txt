cmake_minimum_required(VERSION 3.12)
project(ExpCalc)

set(CMAKE_CXX_STANDARD 17)

add_executable(ExpCalc main.cpp ExpCalc/ExpCalc.cpp ExpCalc/Simplify.cpp)