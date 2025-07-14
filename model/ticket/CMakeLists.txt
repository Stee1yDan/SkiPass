cmake_minimum_required(VERSION 3.16)
project(ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(ticket INTERFACE)

target_include_directories(ticket INTERFACE include)