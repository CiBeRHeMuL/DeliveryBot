#pragma once

#include "ConfigException.h"

class WrongSettingTypeException : public ConfigException {
public:
	explicit WrongSettingTypeException(const string &msg) : ConfigException(msg) {}

	WrongSettingTypeException(const string &expectedType, const string &realType)
		: ConfigException("Trying to get a " + expectedType + " value while the field has the type " + realType)
	{}
};
