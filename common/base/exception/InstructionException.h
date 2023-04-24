#pragma once

#include "ExceptionBase.h"

class InstructionException : public virtual ExceptionBase {
public:
	InstructionException(const string &msg) : ExceptionBase(msg) {}
};
