cmake_minimum_required(VERSION 3.16)
project(limited_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(limited_ticket STATIC source/limited_ticket.cpp)

target_include_directories(limited_ticket PUBLIC
        include)

target_link_libraries(limited_ticket PUBLIC abstract_ticket)
