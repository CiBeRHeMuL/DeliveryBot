#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoAbstract.h"
#include "../../config/setting/SettingInterface.h"

#include <mosquitto.h>
#include <string>
#include <functional>
#include <thread>
#include <utility>

using namespace std;

class MosquittoSubscriber : public virtual MosquittoAbstract {
protected:
	function<void(mosquitto *, void *, const mosquitto_message *)> m_callback;

	thread m_thread;
	bool m_isListening = false;

	/** Конфиг */
	string m_topic;
	int m_QoS;

	void readConfig(SettingInterface &config) {
		try {
			m_topic = static_cast<string>(config["topic"]);
			m_QoS = static_cast<int>(config["QoS"]);
			m_clientId = static_cast<string>(config["clientId"]);
		} catch (...) {
			throw MosquittoException("Invalid config");
		}
	}

public:
	MosquittoSubscriber(SettingInterface *config, void (*callback) (mosquitto *, void *, const mosquitto_message *))
		: MosquittoAbstract(), m_callback(callback), m_QoS(), m_topic()
	{
		readConfig(*config);
		connectToMQTTBroker();
		int subRes = mosquitto_subscribe(m_mosquitto, m_msgId, m_topic.c_str(), m_QoS);
		if (subRes != MOSQ_ERR_SUCCESS) {
			throw MosquittoException("Failed to subscribe to topic " + m_topic);
		}
		mosquitto_message_callback_set(
			m_mosquitto,
			callback
		);
	}

	~MosquittoSubscriber() {

		if (m_isListening) {
			mosquitto_loop_stop(m_mosquitto, false);
		}
		mosquitto_unsubscribe(m_mosquitto, m_msgId, m_topic.c_str());
	}

	void startListen() {
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
