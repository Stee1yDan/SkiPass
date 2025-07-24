cmake_minimum_required(VERSION 3.16)
project (tourniquet_service)

set(CMAKE_CXX_STANDARD 23)

add_library(tourniquet_service STATIC source/tourniquet_service.cpp)

target_include_directories(tourniquet_service PUBLIC include)
target_link_libraries(tourniquet_service PUBLIC
        abstract_ticket
        abstract_storage_unit_repository
        ticket_repository
        extendable_ticket)