#pragma once

#include "../../common/base/exception/ExceptionBase.h"

class BotCommandException : public virtual ExceptionBase {
public:
	BotCommandException(const string &msg) : ExceptionBase(msg) {}
};
