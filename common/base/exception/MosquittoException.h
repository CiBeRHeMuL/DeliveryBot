#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class MosquittoException : public runtime_error {
public:
	explicit MosquittoException(const string &msg) : runtime_error(msg) {}
};
