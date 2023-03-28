#pragma once

#include <map>
#include <string>

using namespace std;

class RequestAbstract {
public:
	virtual map<string, string> getData() = 0;

	virtual string getData(const string &key) = 0;
};
