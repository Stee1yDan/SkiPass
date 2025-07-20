cmake_minimum_required(VERSION 3.31)
project(SkiPass)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(application)
add_subdirectory(configuration)
add_subdirectory(controller)
add_subdirectory(model)
add_subdirectory(repository)
add_subdirectory(service)
add_subdirectory(utils)
add_subdirectory(view)

configure_file(application/banner.txt application/banner.txt COPYONLY)

