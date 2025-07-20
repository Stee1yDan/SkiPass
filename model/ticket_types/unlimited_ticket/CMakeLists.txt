cmake_minimum_required(VERSION 3.16)
project(unlimited_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(unlimited_ticket STATIC source/unlimited_ticket.cpp)

target_include_directories(unlimited_ticket PUBLIC
        include)

target_link_libraries(unlimited_ticket PUBLIC abstract_ticket transferable_ticket)
