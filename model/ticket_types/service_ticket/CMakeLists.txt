cmake_minimum_required(VERSION 3.16)
project(service_ticket)

set(CMAKE_CXX_STANDARD 23)

add_library(service_ticket STATIC source/service_ticket.cpp)

target_include_directories(service_ticket PUBLIC
        include)

target_link_libraries(service_ticket PUBLIC abstract_ticket transferable_ticket)
