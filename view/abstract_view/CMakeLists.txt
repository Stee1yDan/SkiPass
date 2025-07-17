cmake_minimum_required(VERSION 3.16)
project(abstract_view)

set(CMAKE_CXX_STANDARD 23)

add_library(view INTERFACE)

target_include_directories(view INTERFACE include)
target_link_libraries(view INTERFACE ticket_service)


