cmake_minimum_required(VERSION 3.16)
project (cli_controller)

set(CMAKE_CXX_STANDARD 23)

add_library(cli_controller STATIC source/cli_controller.cpp)

target_include_directories(cli_controller PUBLIC include)
target_link_libraries(cli_controller PUBLIC
        ticket
        ticket_service
        unlimited_ticket
        controller)