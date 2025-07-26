cmake_minimum_required(VERSION 3.16)
project (ticket_service)

set(CMAKE_CXX_STANDARD 23)

add_library(ticket_service STATIC source/ticket_service.cpp)

target_include_directories(ticket_service PUBLIC include)
target_link_libraries(ticket_service PUBLIC
        abstract_ticket
        abstract_storage_unit_repository
        ticket_repository
        extendable_ticket
        transferable_ticket)