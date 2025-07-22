cmake_minimum_required(VERSION 3.16)
project(storage_unit)

set(CMAKE_CXX_STANDARD 23)

add_library(storage_unit STATIC source/storage_unit.cpp)

target_include_directories(storage_unit PUBLIC
        include)
target_link_libraries(storage_unit PUBLIC abstract_ticket)