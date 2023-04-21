#pragma once

#include "ExceptionBase.h"

class MosquittoException : public ExceptionBase {
public:
	explicit MosquittoException(const string &msg) : ExceptionBase(msg) {}
};
