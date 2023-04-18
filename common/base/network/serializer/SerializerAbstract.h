#pragma once

#include "SerializerInterface.h"

template<class T>
class SerializerAbstract : public virtual SerializerInterface<T> {
public:
	string serialize(const T &data) {
		return {};
	}
};
