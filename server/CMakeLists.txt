set(SERVER_EXE_NAME "${PROJECT_NAME}Server")

set(CMAKE_PREFIX_PATH "C:/Program Files (x86)/OpenCV/install/opencv/x64/vc17/lib/")

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(${SERVER_EXE_NAME} main.cpp base/bot/Bot.h base/order/OrderAbstract.h base/camera/CameraAbstract.h)

target_link_libraries(${SERVER_EXE_NAME} ${OpenCV_LIBS})

cmake_path(GET OpenCV_DIR PARENT_PATH OpenCV_PARENT_DIR)
set(OpenCV_PARENT_DIR ${OpenCV_PARENT_DIR}/bin/)

file(GLOB DLLS RELATIVE "${OpenCV_PARENT_DIR}" "${OpenCV_PARENT_DIR}/*.dll")
foreach(DLL ${DLLS})
    add_custom_command(
            TARGET ${SERVER_EXE_NAME}
            COMMAND ${CMAKE_COMMAND}
            -E copy "${OpenCV_PARENT_DIR}/${DLL}" "${CMAKE_BINARY_DIR}/${DLL}"
    )
endforeach()