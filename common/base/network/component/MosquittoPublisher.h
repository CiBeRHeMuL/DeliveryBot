#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoSettings.h"
#include "MosquittoAbstract.h"
#include "../../config/Config.h"

#include <libconfig.h++>
#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoPublisher : protected virtual MosquittoAbstract {
protected:
	/** Конфиг */
	string m_topic;
	int m_QoS;
	bool m_retaining;

	void readConfig(const libconfig::Config &config) {
		libconfig::Setting &root = config.getRoot().lookup("Publisher");
		if (!root.exists("topic") || !root.exists("qos") || !root.exists("retaining")) {
			throw MosquittoException("Bad config");
		}
		try {
			root.lookupValue("topic", m_topic);
			root.lookupValue("qos", m_QoS);
			root.lookupValue("retaining", m_retaining);
		} catch (...) {
			throw MosquittoException("Failed to read config");
		}
	}

	explicit MosquittoPublisher(const libconfig::Config &config) : MosquittoAbstract(), m_QoS(), m_topic(), m_retaining() {
		readConfig(config);
	}

public:
	static MosquittoPublisher *getInstance() {
		static MosquittoPublisher mosquittoPublisher(Config::getConfig());
		return &mosquittoPublisher;
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
