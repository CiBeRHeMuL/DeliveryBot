cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "DeliveryBot")
set(CMAKE_CXX_STANDARD 20)

project(${PROJECT_NAME})

set(INCLUDE_DIR "/usr/include")

include_directories(${INCLUDE_DIR})

add_subdirectory(bot)
add_subdirectory(server)
add_subdirectory(tests)
