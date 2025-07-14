cmake_minimum_required(VERSION 3.16)
project(abstract_controller)

set(CMAKE_CXX_STANDARD 23)

add_library(controller INTERFACE)

target_include_directories(controller INTERFACE include ticket_service)
target_link_libraries(controller INTERFACE
            ticket_service)
