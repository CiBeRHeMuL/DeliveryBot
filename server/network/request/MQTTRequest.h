#pragma once

#include "../../../common/base/network/request/RequestAbstract.h"
#include "../../../common/network/serializer/MapSerializer.h"
#include "../component/ServerMosquittoPublisher.h"

template<class T = map<string, string>>
class MQTTRequest : public virtual RequestAbstract<T> {
protected:
	ServerMosquittoPublisher *m_publisher;

public:
	explicit MQTTRequest(SerializerInterface<T> *serializer) : RequestAbstract<T>(serializer) {
		m_publisher = ServerMosquittoPublisher::getInstance();
	}

protected:
	bool sendData() override {
		return m_publisher->publishMessage(this->m_rawBody);
	}
};
