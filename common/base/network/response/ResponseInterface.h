#pragma once

#include <string>

using namespace std;

class ResponseInterface {
protected:
	string m_rawBody = {};

public:
	virtual string getRawBody() {
		return m_rawBody;
	}

	virtual bool send() = 0;
};
