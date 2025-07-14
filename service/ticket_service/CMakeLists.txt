cmake_minimum_required(VERSION 3.16)
project (ticket_service)

set(CMAKE_CXX_STANDARD 23)

add_library(ticket_service STATIC source/ticket_service.cpp)

target_include_directories(ticket_service PUBLIC include)
target_link_libraries(ticket_service PUBLIC ticket abstract_ticket ticket_repository)