cmake_minimum_required(VERSION 3.16)
project(transferable_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(transferable_ticket STATIC source/transferable_ticket.cpp)

target_include_directories(transferable_ticket PUBLIC
        include)
target_link_libraries(transferable_ticket PUBLIC abstract_ticket)