cmake_minimum_required(VERSION 3.16)
project (service)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(ticket_service)
add_subdirectory(storage_service)
add_subdirectory(tourniquet_service)