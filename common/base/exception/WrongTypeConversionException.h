#pragma once

#include "WrongSettingTypeException.h"

class WrongTypeConversionException : public WrongSettingTypeException {
public:
	WrongTypeConversionException(const string &msg) : WrongSettingTypeException(msg) {}

	WrongTypeConversionException(const string &fromType, const string &toType)
		: WrongSettingTypeException("Cannot convert type " + fromType + " to type " + toType)
	{}
};
