#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoSettings.h"

#include <mosquitto.h>
#include <string>

using namespace std;

class MosquittoAbstract {
protected:
	mosquitto *m_mosquitto;

	int *m_msgId;

public:
	MosquittoAbstract() : m_msgId(new int(0)) {
		m_mosquitto = mosquitto_new(MOSQUITTO_CLIENT_ID, false, nullptr);
		if (m_mosquitto == nullptr) {
			throw MosquittoException("Failed to instantiate mosquitto client");
		} else {
			int connectRes = mosquitto_connect(m_mosquitto, MOSQUITTO_HOST, MOSQUITTO_PORT, MOSQUITTO_KEEPALIVE_SECONDS);
			if (connectRes != MOSQ_ERR_SUCCESS) {
				throw MosquittoException("Failed to connect to mosquitto broker");
			}
		}
	}

	~MosquittoAbstract() {
		mosquitto_disconnect(m_mosquitto);
		mosquitto_destroy(m_mosquitto);
		m_mosquitto = nullptr;
		m_msgId = nullptr;
	}
};
