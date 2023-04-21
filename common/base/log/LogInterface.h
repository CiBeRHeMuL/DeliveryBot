#pragma once

#include "LogLevel.h"

#include <string>

using namespace std;

class LogInterface {
public:
	virtual void log(const string &message, LogLevel level) = 0;
};
