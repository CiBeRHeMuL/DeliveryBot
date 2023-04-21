#pragma once

#include "ConfigException.h"

class InvalidConfigException : public virtual ConfigException {
public:
	InvalidConfigException(const string &msg) : ConfigException(msg) {}
};
