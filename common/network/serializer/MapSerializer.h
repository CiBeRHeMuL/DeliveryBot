#pragma once

#include "../../base/network/serializer/SerializerAbstract.h"

#include <map>

template<class Key, class Data>
class MapSerializer : public SerializerAbstract<map<Key, Data>> {
public:
	string serialize(const map<Key, Data> &data) {
		string result;
		for (auto &p : data) {
			result += p.first + ":" + p.second + "\r\n";
		}
		return result;
	}
};
