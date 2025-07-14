cmake_minimum_required(VERSION 3.16)
project(abstract_app_builder)

set(CMAKE_CXX_STANDARD 23)

add_library(abstract_app_builder INTERFACE)

target_include_directories(abstract_app_builder INTERFACE include)
target_link_libraries(abstract_app_builder INTERFACE
	cli_controller
	ticket_repository
	ticket_service
)