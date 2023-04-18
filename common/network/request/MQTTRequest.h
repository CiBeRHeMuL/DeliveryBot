#pragma once

#include "../../base/network/request/RequestAbstract.h"
#include "../serializer/MapSerializer.h"
#include "../../base/network/component/MosquittoPublisher.h"

class MQTTRequest : public RequestAbstract {
protected:
	MosquittoPublisher *m_publisher;

public:
	MQTTRequest() : RequestAbstract(new MapSerializer<string, string>) {
		m_publisher = MosquittoPublisher::getInstance();
	}

protected:
	bool sendData() override {
		return m_publisher->publishMessage(m_rawBody);
	}
};
