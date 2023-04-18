#pragma once

#include "RequestInterface.h"
#include "../serializer/SerializerInterface.h"

#include <map>

class RequestAbstract : public virtual RequestInterface {
protected:
	map<string, string> m_data = {};

	SerializerInterface<map<string, string>> *m_serializer;

	/**
	 * Needs to update body
	 */
	bool m_dataUpdated = false;

public:
	explicit RequestAbstract(SerializerInterface<map<string, string>> *serializer) : m_serializer(serializer) {}

	~RequestAbstract() {
		m_serializer = nullptr;
		m_data.clear();
	}

	map<string, string> getData() {
		return m_data;
	}

	string getData(const string &key, const string &defaultValue = "") {
		try {
			return m_data.at(key);
		} catch (...) {
			return defaultValue;
		}
	}

	void setData(map<string, string> &&data) {
		m_data = data;
		m_dataUpdated = true;
	}

	void addData(map<string, string> &&data) {
		m_data.merge(data);
		m_dataUpdated = true;
	}

	void addData(const string& key, const string& datum) {
		m_data[key] = datum;
		m_dataUpdated = true;
	}

	bool send() override {
		if (m_dataUpdated) {
			m_rawBody = m_serializer->serialize(m_data);
		}
		return sendData();
	}

	string getRawBody() override {
		if (m_dataUpdated) {
			m_rawBody = m_serializer->serialize(m_data);
		}
		return RequestInterface::getRawBody();
	}

protected:
	virtual bool sendData() = 0;
};
