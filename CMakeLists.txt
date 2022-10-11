cmake_minimum_required(VERSION 3.23)
project(mos)

find_package(Boost REQUIRED)

set(CMAKE_CXX_STANDARD 17)

macro(SUBDIRLIST result curdir)
    file(GLOB children ${curdir} ${curdir}/*)
    set(dirlist "")
    foreach(child ${children})
        if(EXISTS "${child}/CMakeLists.txt")
            LIST(APPEND dirlist ${child})
        endif()
    endforeach()
    set(${result} ${dirlist})
endmacro()

SUBDIRLIST(SUBDIRS plugins)

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()

add_executable(mos main.cpp plugins/t2/main.cpp)
