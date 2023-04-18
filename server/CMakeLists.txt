set(SERVER_EXE_NAME "${PROJECT_NAME}Server")

set(CMAKE_PREFIX_PATH "/mnt/c/lib/opencv/build")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${SERVER_EXE_NAME} main.cpp)

target_link_libraries(${SERVER_EXE_NAME} ${OpenCV_LIBS})
target_link_libraries(${SERVER_EXE_NAME} mosquitto)
target_link_libraries(${SERVER_EXE_NAME} config++)
