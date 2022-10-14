cmake_minimum_required(VERSION 3.23)
project(mos_plugin)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

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

include_directories(
        ${Boost_INCLUDE_DIRS}
)

link_directories(
        ${Boost_LIBRARY_DIRS}
)

SUBDIRLIST(SUBDIRS plugins)

foreach(subdir ${SUBDIRS})
    add_subdirectory(${subdir})
endforeach()

