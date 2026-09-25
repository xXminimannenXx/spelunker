cmake_minimum_required(VERSION 3.15)
project(spelunker VERSION 0.3.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(spelunker spelunker.cpp)
if(MSVC)
    set_property(TARGET spelunker PROPERTY
        MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
else()
    target_link_options(spelunker PRIVATE -static)
endif()
if(MSVC)
    target_compile_options(spelunker PRIVATE /W4)
else()
    target_compile_options(spelunker PRIVATE -Wall -Wextra)
endif()