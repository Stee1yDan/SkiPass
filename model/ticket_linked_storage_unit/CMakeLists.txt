cmake_minimum_required(VERSION 3.16)
project(ticket_linked_storage_unit)

set(CMAKE_CXX_STANDARD 23)

add_library(ticket_linked_storage_unit STATIC source/ticket_linked_storage_unit.cpp)

target_include_directories(ticket_linked_storage_unit PUBLIC
        include)

target_link_libraries(ticket_linked_storage_unit PUBLIC
        storage_unit
        abstract_ticket)
