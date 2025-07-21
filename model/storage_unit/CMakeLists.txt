cmake_minimum_required(VERSION 3.16)
project(storage_unit)

set(CMAKE_CXX_STANDARD 23)

add_library(storage_unit INTERFACE)

target_include_directories(storage_unit INTERFACE include)