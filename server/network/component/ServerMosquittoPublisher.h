#pragma once

#include "../../../common/base/network/component/MosquittoPublisher.h"
#include "../../app/ServerApplication.h"

void mosqLog(mosquitto *mosq, void *user, int level, const char *msg) {
	LogLevel lLevel;
	switch (level) {
		case MOSQ_LOG_WARNING:
			lLevel = LEVEL_WARNING;
			break;
		case MOSQ_LOG_DEBUG:
			lLevel = LEVEL_TRACE;
			break;
		case MOSQ_LOG_INFO:
		case MOSQ_LOG_NOTICE:
			lLevel = LEVEL_INFO;
			break;
		case MOSQ_LOG_ERR:
		default:
			lLevel = LEVEL_ERROR;
			break;
	}
	ServerApplication::getApp()->getLogger()->log({msg}, lLevel);
}

void mosqReconnect(mosquitto *mosq, void *user, int rc) {
	ServerApplication::getApp()->getLogger()->warning("MQTT broker disconnected with code " + to_string(rc));
}

class ServerMosquittoPublisher : public MosquittoPublisher {
public:
	explicit ServerMosquittoPublisher(SettingInterface *config) : MosquittoPublisher(config) {}

	void init() override {
		MosquittoPublisher::init();
		mosquitto_log_callback_set(m_mosquitto, mosqLog);
		mosquitto_disconnect_callback_set(m_mosquitto, mosqReconnect);
	}

	static ServerMosquittoPublisher *getInstance(SettingInterface *config = nullptr) {
		static ServerMosquittoPublisher *instance = nullptr;
		if (instance == nullptr && config != nullptr) {
			instance = new ServerMosquittoPublisher(config);
			instance->init();
		} else if (instance == nullptr && config == nullptr) {
			throw MosquittoException("Cannot initialize ServerMosquittoPublisher without config");
		}
		return instance;
	}
};
