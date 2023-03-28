set(BOT_EXE_NAME "${PROJECT_NAME}Bot")

add_executable(${BOT_EXE_NAME} main.cpp base/engine/EngineAbstract.h ../common/base/direction/DirectionAbstract.h EngineManager.h ../common/base/request/RequestAbstract.h ../common/base/response/ResponseAbstract.h ../common/base/exception/DirectionException.h ../common/enums/BotState.h)