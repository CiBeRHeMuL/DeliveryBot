set(BOT_EXE_NAME "${PROJECT_NAME}Bot")

add_executable(${BOT_EXE_NAME} main.cpp base/engine/EngineAbstract.h ../common/base/direction/DirectionAbstract.h EngineManager.h ../common/base/network/request/RequestInterface.h ../common/base/exception/DirectionException.h ../common/enums/BotStatus.h ../common/network/request/MQTTRequest.h ../common/base/network/request/RequestAbstract.h)

target_link_libraries(${BOT_EXE_NAME} mosquitto)
target_link_libraries(${BOT_EXE_NAME} config++)
