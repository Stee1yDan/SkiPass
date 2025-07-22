cmake_minimum_required(VERSION 3.16)
project (application)

set(CMAKE_CXX_STANDARD 23)

add_library(skipass_app STATIC source/skipass_app.cpp banner.txt)

target_include_directories(skipass_app PUBLIC include)
target_link_libraries(skipass_app PUBLIC in_memory_app_builder unlimited_ticket abstract_ticket)

add_executable(skipass source/main.cpp)
target_link_libraries(skipass PUBLIC
        abstract_ticket
        unlimited_ticket
        ticket_service
        skipass_app
        abstract_app_builder
        abstract_storage_unit_repository
        in_memory_storage_unit_repository
        in_memory_app_builder
        ticket_repository
        in_memory_ticket_repository
)