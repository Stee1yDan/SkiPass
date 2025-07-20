cmake_minimum_required(VERSION 3.16)
project(extendable_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(extendable_ticket STATIC source/extendable_ticket.cpp)

target_include_directories(extendable_ticket PUBLIC
        include)
target_link_libraries(extendable_ticket PUBLIC abstract_ticket)