cmake_minimum_required(VERSION 3.16)
project(time_utils)

set(CMAKE_CXX_STANDARD 23)

add_library(time_utils STATIC source/time_utils.cpp)

target_include_directories(time_utils PUBLIC
        include)

target_link_libraries(temporary_ticket PUBLIC)
