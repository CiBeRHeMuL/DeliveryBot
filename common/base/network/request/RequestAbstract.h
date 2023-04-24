#pragma once

#include "RequestInterface.h"
#include "../serializer/SerializerInterface.h"

#include <map>

template<class T>
class RequestAbstract : public virtual RequestInterface<T> {
protected:
	T m_data = {};

	SerializerInterface<T> *m_serializer;

	string m_rawBody;

	/**
	 * Needs to update body
	 */
	bool m_dataUpdated = false;

public:
	RequestAbstract(SerializerInterface<T> *serializer) : RequestInterface<T>(), m_serializer(serializer) {}

	~RequestAbstract() {
		m_serializer = nullptr;
	}

	T getData() override {
		return m_data;
	}

	void setData(const T &data) override {
		m_data = data;
		m_dataUpdated = true;
	}

	void setData(T &&data) override {
		m_data = std::move(data);
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
		return m_rawBody;
	}

protected:
	virtual bool sendData() = 0;
};
