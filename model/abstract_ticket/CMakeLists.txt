cmake_minimum_required(VERSION 3.16)
project(abstract_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(abstract_ticket STATIC source/abstract_ticket.cpp)

target_include_directories(abstract_ticket PUBLIC
        include)

target_link_libraries(abstract_ticket PUBLIC ticket)