#pragma once

#include "ExceptionBase.h"

class RequestException : public ExceptionBase {
public:
	explicit RequestException(const string &msg) : ExceptionBase(msg) {}
};
