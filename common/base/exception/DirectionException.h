#pragma once

#include "ExceptionBase.h"

class DirectionException : public ExceptionBase {
public:
	explicit DirectionException(const string &msg) : ExceptionBase(msg) {}
};
