#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class ExceptionBase : public runtime_error {
public:
	explicit ExceptionBase(const string &msg) : runtime_error(msg) {}
};