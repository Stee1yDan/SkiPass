cmake_minimum_required(VERSION 3.16)
project (storage_service)

set(CMAKE_CXX_STANDARD 23)

add_library(storage_service STATIC source/storage_service.cpp)

target_include_directories(storage_service PUBLIC include)
target_link_libraries(storage_service PUBLIC
        abstract_ticket
        abstract_storage_unit_repository
        ticket_repository
        extendable_ticket)