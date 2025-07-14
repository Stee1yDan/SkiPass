cmake_minimum_required(VERSION 3.16)
project(ticket_repository)

set(CMAKE_CXX_STANDARD 23)

add_library(ticket_repository INTERFACE)

target_include_directories(ticket_repository INTERFACE include)