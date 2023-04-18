#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class RequestException : public runtime_error {
public:
	explicit RequestException(const string &msg) : runtime_error(msg) {}
};
