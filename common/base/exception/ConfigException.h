#pragma once

#include "ExceptionBase.h"

class ConfigException : public ExceptionBase {
public:
	explicit ConfigException(const string &msg) : ExceptionBase(msg) {}
};
