#pragma once

#include <string>

using namespace std;

class CommandInterface {
public:
	virtual ~CommandInterface() = default;

	virtual void setInstruction(const string &key, const string &data) = 0;

	virtual string toQueryString() const = 0;
};
