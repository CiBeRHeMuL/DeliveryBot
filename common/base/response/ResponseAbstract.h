#pragma once

#include <map>
#include <string>

using namespace std;

class ResponseAbstract {
public:
	virtual bool send(const map<string, string> &data) = 0;
};
