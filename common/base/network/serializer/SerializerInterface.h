#pragma once

#include <string>

using namespace std;

template<class T>
class SerializerInterface {
public:
	virtual string serialize(const T &data) = 0;
};
