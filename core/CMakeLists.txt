cmake_minimum_required(VERSION 3.23)
project(mos)

find_package(Boost REQUIRED COMPONENTS filesystem)

set(CMAKE_CXX_STANDARD 14)
add_executable(mos src/main.cpp src/queue.cpp src/core.cpp src/node.cpp)

target_include_directories(
        mos
        PRIVATE include
)

target_link_libraries(mos ${Boost_LIBRARIES})