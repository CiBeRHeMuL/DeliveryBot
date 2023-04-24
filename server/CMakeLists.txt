set(SERVER_EXE_NAME "${PROJECT_NAME}Server")

find_package(nlohmann_json 3.2.0 REQUIRED)
find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${SERVER_EXE_NAME} main.cpp)

target_link_libraries(${SERVER_EXE_NAME} mosquitto)
target_link_libraries(${SERVER_EXE_NAME} nlohmann_json::nlohmann_json)
