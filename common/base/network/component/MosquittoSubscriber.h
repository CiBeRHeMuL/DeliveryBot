#pragma once

#include "../../exception/MosquittoException.h"
#include "MosquittoSettings.h"
#include "MosquittoAbstract.h"

#include <libconfig.h++>
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

	void readConfig(const libconfig::Config &config) {
		libconfig::Setting &root = config.getRoot();
		if (!root.exists("topic") || !root.exists("qos")) {
			throw MosquittoException("Bad config");
		}
		try {
			root.lookupValue("topic", m_topic);
			root.lookupValue("qos", m_QoS);
		} catch (...) {
			throw MosquittoException("Failed to read config");
		}
	}

public:
	MosquittoSubscriber(const libconfig::Config &config, void (*callback) (mosquitto *, void *, const mosquitto_message *))
		: MosquittoAbstract(), m_callback(callback), m_QoS(), m_topic()
	{
		readConfig(config);
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

	void stopListen() {
		if (m_isListening) {
			mosquitto_loop_stop(m_mosquitto, true);
			m_isListening = false;
		}
	}
};
