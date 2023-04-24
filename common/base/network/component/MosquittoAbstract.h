#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoSettings.h"

#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoAbstract {
protected:
	mosquitto *m_mosquitto{};

	int *m_msgId;

	bool m_isInitiated = false;

	/**
	 * Сщташп
	 */
	string m_clientId = MOSQUITTO_CLIENT_ID;
	string m_host = MOSQUITTO_HOST;
	int m_port = MOSQUITTO_PORT;
	int m_keepAliveSec = MOSQUITTO_KEEPALIVE_SECONDS;
	string m_topic = MOSQUITTO_DEFAULT_TOPIC;
	int m_QoS = MOSQUITTO_DEFAULT_QoS;
	bool m_retaining = MOSQUITTO_DEFAULT_MESSAGE_RETAINING;

public:
	explicit MosquittoAbstract() : m_msgId(new int(0)) {}

	/**
	 * Must be called after instantiation
	 */
	virtual void init() {
		mosquitto_lib_init();
		m_mosquitto = mosquitto_new(m_clientId.c_str(), false, nullptr);
		if (m_mosquitto == nullptr) {
			throw MosquittoException("Failed to instantiate mosquitto client");
		}
		m_isInitiated = true;
	}

	~MosquittoAbstract() {
		mosquitto_destroy(m_mosquitto);
		m_mosquitto = nullptr;
		m_msgId = nullptr;
		mosquitto_lib_cleanup();
	}
};
