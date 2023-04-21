#pragma once

#include "LogAbstract.h"

#include <iostream>
#include <map>

class ConsoleLog : public virtual LogAbstract {
protected:
	map<LogLevel, string> headersColor = {
		{LogLevel::LEVEL_ERROR, "31"},
		{LogLevel::LEVEL_WARNING, "33"},
		{LogLevel::LEVEL_INFO, "37"},
		{LogLevel::LEVEL_TRACE, "32"},
	};
	map<LogLevel, string> headers = {
		{LogLevel::LEVEL_ERROR, "ERROR"},
		{LogLevel::LEVEL_WARNING, "WARNING"},
		{LogLevel::LEVEL_INFO, "INFO"},
		{LogLevel::LEVEL_TRACE, "TRACE"},
	};

	string getHeader(LogLevel level) {
		return "\033[1;"s + headersColor[level] + "m["s + headers[level] + "] \033[0m"s;
	}

public:
	void log(const string &message, LogLevel level) override {
		string output = getHeader(level) + message + "\n";
		cerr << output;
	}
};
