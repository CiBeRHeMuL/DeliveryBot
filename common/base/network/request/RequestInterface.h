#pragma once

#include <string>

using namespace std;

template<class T>
class RequestInterface {
public:
	virtual string getRawBody() = 0;

	virtual T getData() = 0;

	virtual void setData(const T &) = 0;

	virtual void setData(T &&) = 0;

	virtual bool send() = 0;
};
