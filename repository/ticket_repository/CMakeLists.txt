cmake_minimum_required(VERSION 3.16)
project (ticket_repository)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(abstract_ticket_repository)
add_subdirectory(in_memory_ticket_repository)
