cmake_minimum_required(VERSION 3.24)

set(PROJECT_NAME "DeliveryBot")
set(CMAKE_CXX_STANDARD 23)

project(${PROJECT_NAME})

add_subdirectory(bot)
add_subdirectory(server)
