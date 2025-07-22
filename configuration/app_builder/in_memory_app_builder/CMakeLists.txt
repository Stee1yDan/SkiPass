cmake_minimum_required(VERSION 3.16)
project (in_memory_app_builder)

set(CMAKE_CXX_STANDARD 23)

add_library(in_memory_app_builder STATIC source/in_memory_app_builder.cpp)

target_include_directories(in_memory_app_builder PUBLIC include)

target_link_libraries(in_memory_app_builder PUBLIC
        abstract_app_builder
        ticket_service
        ticket_repository
        abstract_storage_unit_repository
        cli_view
        in_memory_ticket_repository
        in_memory_storage_unit_repository
)
