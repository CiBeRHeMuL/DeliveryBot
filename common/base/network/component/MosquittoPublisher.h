#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoAbstract.h"
#include "../../config/setting/IniSetting.h"

#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoPublisher : protected virtual MosquittoAbstract {
protected:
	/** Конфиг */
	string m_topic;
	int m_QoS;
	bool m_retaining;

	void readConfig(SettingInterface &config) {
		try {
			m_topic = static_cast<string>(config["topic"]);
			m_QoS = static_cast<int>(config["QoS"]);
			m_retaining = static_cast<bool>(config["retaining"]);
			m_clientId = static_cast<string>(config["clientId"]);
		} catch (...) {
			throw MosquittoException("Invalid config");
		}
	}

public:
	explicit MosquittoPublisher(SettingInterface *config) : MosquittoAbstract(), m_QoS(), m_topic(), m_retaining() {
		readConfig(*config);
		connectToMQTTBroker();
	}

	~MosquittoPublisher() = default;

	static MosquittoPublisher *getInstance(SettingInterface *config = nullptr) {
		static MosquittoPublisher *instance = nullptr;
		if (instance == nullptr && config != nullptr) {
			instance = new MosquittoPublisher(config);
		} else if (instance == nullptr && config == nullptr) {
			throw MosquittoException("Cannot initialize MosquittoPublisher without config");
		}
		return instance;
	}

	bool publishMessage(const string &msg) {
		return mosquitto_publish(
			m_mosquitto,
			m_msgId,
			m_topic.c_str(),
			static_cast<int>(msg.length()),
			reinterpret_cast<const void *>(msg.c_str()),
			m_QoS,
			m_retaining
		) == MOSQ_ERR_SUCCESS;
	}
};
