cmake_minimum_required(VERSION 3.16)
project (ticket_types)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(limited_ticket)
add_subdirectory(service_ticket)
add_subdirectory(temporary_ticket)
add_subdirectory(unlimited_ticket)

