cmake_minimum_required(VERSION 3.23)
project(mmos)

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)

add_executable(mmos main.cpp)
