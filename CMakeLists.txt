cmake_minimum_required(VERSION 3.15)
project(spelunker VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spelunker spelunker.cpp)

if(MSVC)
    target_compile_options(spelunker PRIVATE /W4)
else()
    target_compile_options(spelunker PRIVATE -Wall -Wextra)
endif()