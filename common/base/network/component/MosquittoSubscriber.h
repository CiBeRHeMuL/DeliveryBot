#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoAbstract.h"
#include "../../config/setting/SettingInterface.h"

#include <mosquitto.h>
#include <string>
#include <functional>
#include <utility>

using namespace std;

class MosquittoSubscriber : public virtual MosquittoAbstract {
protected:
	void (*m_callback)(mosquitto *, void *, const mosquitto_message *);

	bool m_isListening = false;

	SettingInterface *m_config;

	void readConfig(SettingInterface &config) {
		try {
			m_topic = static_cast<string>(config["topic"]);
			m_QoS = static_cast<int>(config["QoS"]);
			m_clientId = static_cast<string>(config["clientId"]);
			m_host = static_cast<string>(config["host"]);
			m_port = static_cast<int>(config["port"]);
			m_keepAliveSec = static_cast<int>(config["keepAliveSec"]);
		} catch (...) {
			throw MosquittoException("Invalid config");
		}
	}

public:
	MosquittoSubscriber(SettingInterface *config, void (*callback) (mosquitto *, void *, const mosquitto_message *))
		: MosquittoAbstract(), m_callback(callback), m_config(config)
	{}

	~MosquittoSubscriber() {
		mosquitto_disconnect(m_mosquitto);
		if (m_isListening) {
			mosquitto_loop_stop(m_mosquitto, false);
		}
		mosquitto_unsubscribe(m_mosquitto, m_msgId, m_topic.c_str());
	}

	void init() override {
		readConfig(*m_config);
		MosquittoAbstract::init();
		int connectRes = mosquitto_connect(m_mosquitto, m_host.c_str(), m_port, m_keepAliveSec);
		if (connectRes != MOSQ_ERR_SUCCESS) {
			throw MosquittoException("Connection to MQTT broker failed");
		}
		int subRes = mosquitto_subscribe(m_mosquitto, m_msgId, m_topic.c_str(), m_QoS);
		if (subRes != MOSQ_ERR_SUCCESS) {
			throw MosquittoException("Failed to subscribe to topic " + m_topic);
		}
		mosquitto_message_callback_set(
				m_mosquitto,
				m_callback
		);
	}

	void startListen() {
		if (!m_isInitiated) {
			throw MosquittoException("Failed to start not initiated subscriber");
		}
		int startRes = mosquitto_loop_start(m_mosquitto);
		if (startRes != MOSQ_ERR_SUCCESS) {
			throw MosquittoException("Failed to start listening loop");
		}
		m_isListening = true;
	}

	bool isListening() const {
		return m_isListening;
	}

	void stopListen() {
		if (m_isListening) {
			mosquitto_loop_stop(m_mosquitto, true);
			m_isListening = false;
		}
	}
};
