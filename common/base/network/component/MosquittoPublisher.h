#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoAbstract.h"
#include "../../config/setting/IniSetting.h"

#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoPublisher : protected virtual MosquittoAbstract {
protected:
	int m_lastResult = MOSQ_ERR_SUCCESS;

	SettingInterface *m_config;

	virtual void readConfig(SettingInterface &config) {
		try {
			m_topic = static_cast<string>(config["topic"]);
			m_QoS = static_cast<int>(config["QoS"]);
			m_retaining = static_cast<bool>(config["retaining"]);
			m_clientId = static_cast<string>(config["clientId"]);
			m_host = static_cast<string>(config["host"]);
			m_port = static_cast<int>(config["port"]);
			m_keepAliveSec = static_cast<int>(config["keepAliveSec"]);
		} catch (...) {
			throw MosquittoException("Invalid config");
		}
	}

	virtual int connect() {
		return mosquitto_connect(m_mosquitto, m_host.c_str(), m_port, m_keepAliveSec);
	}

public:
	explicit MosquittoPublisher(SettingInterface *config) : m_config(config), MosquittoAbstract() {}

	~MosquittoPublisher() = default;

	void init() override {
		readConfig(*m_config);
		MosquittoAbstract::init();
	}

	static MosquittoPublisher *getInstance(SettingInterface *config = nullptr) {
		static MosquittoPublisher *instance = nullptr;
		if (instance == nullptr && config != nullptr) {
			instance = new MosquittoPublisher(config);
			instance->init();
		} else if (instance == nullptr && config == nullptr) {
			throw MosquittoException("Cannot initialize MosquittoPublisher without config");
		}
		return instance;
	}

	bool publishMessage(const string &msg) {
		if (!m_isInitiated) {
			throw MosquittoException("Failed to publish via not initiated publisher+");
		}
		int connectRes = connect();
		if (connectRes != MOSQ_ERR_SUCCESS) {
			throw MosquittoException("Failed to connect to mosquitto broker");
		}
		m_lastResult = mosquitto_publish(
			m_mosquitto,
			m_msgId,
			m_topic.c_str(),
			static_cast<int>(msg.length()),
			reinterpret_cast<const void *>(msg.c_str()),
			m_QoS,
			m_retaining
		);
		mosquitto_disconnect(m_mosquitto);
		return m_lastResult == MOSQ_ERR_SUCCESS;
	}

	int getLastResult() const {
		return m_lastResult;
	}
};
