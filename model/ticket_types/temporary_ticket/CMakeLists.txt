cmake_minimum_required(VERSION 3.16)
project(temporary_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(temporary_ticket STATIC source/temporary_ticket.cpp)

target_include_directories(temporary_ticket PUBLIC
        include)

target_link_libraries(temporary_ticket PUBLIC abstract_ticket)
