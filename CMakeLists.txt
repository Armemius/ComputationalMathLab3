cmake_minimum_required(VERSION 3.13)
project(ComputationalMathLab3 VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(NOT CMAKE_CXX_EXTENSIONS)
    set(CMAKE_CXX_EXTENSIONS OFF)
endif()


file(GLOB_RECURSE sources CONFIGURE_DEPENDS
        src/*.cpp
        src/*.hpp
        include/*.hpp
)

add_executable(ComputationalMathLab3 ${sources})
target_include_directories(ComputationalMathLab3 PRIVATE src include libs)