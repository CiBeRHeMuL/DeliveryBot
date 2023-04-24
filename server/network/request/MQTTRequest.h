#pragma once

#include "../../../common/base/network/request/RequestAbstract.h"
#include "../../../common/base/network/serializer/SerializerAbstract.h"
#include "../component/ServerMosquittoPublisher.h"

template<class T = map<string, string>>
class MQTTRequest : public virtual RequestAbstract<T> {
protected:
	ServerMosquittoPublisher *m_publisher;

public:
	explicit MQTTRequest(SerializerAbstract<T> *serializer) : RequestAbstract<T>(serializer) {
		m_publisher = ServerMosquittoPublisher::getInstance();
	}

protected:
	bool sendData() override {
		return m_publisher->publishMessage(this->m_rawBody);
	}
};
