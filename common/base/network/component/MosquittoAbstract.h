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

	string m_clientId = "mosq_client_id";

	/**
	 * Надо вызвать в конструкторе для загрузки id клиента из конфига
	 */
	void connectToMQTTBroker() {
		m_mosquitto = mosquitto_new(m_clientId.c_str(), false, nullptr);
		if (m_mosquitto == nullptr) {
			throw MosquittoException("Failed to instantiate mosquitto client");
		} else {
			int connectRes = mosquitto_connect(m_mosquitto, MOSQUITTO_HOST, MOSQUITTO_PORT, MOSQUITTO_KEEPALIVE_SECONDS);
			if (connectRes != MOSQ_ERR_SUCCESS) {
				throw MosquittoException("Failed to connect to mosquitto broker");
			}
		}
	}

public:
	explicit MosquittoAbstract(bool loadMQTTLazy = true) : m_msgId(new int(0)) {
		if (!loadMQTTLazy) {
			connectToMQTTBroker();
		}
	}

	~MosquittoAbstract() {
		mosquitto_disconnect(m_mosquitto);
		mosquitto_destroy(m_mosquitto);
		m_mosquitto = nullptr;
		m_msgId = nullptr;
	}
};
