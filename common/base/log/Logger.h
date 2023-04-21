#pragma once

#include "LogInterface.h"

class Logger {
protected:
	LogInterface *m_log;

public:
	Logger(LogInterface *log) {
		m_log = log;
	}

	LogInterface *getLog() {
		return m_log;
	}

	void log(const string &msg, LogLevel level) {
		getLog()->log(msg, level);
	}

	void error(const string &msg) {
		getLog()->log(msg, LogLevel::LEVEL_ERROR);
	}

	void warning(const string &msg) {
		getLog()->log(msg, LogLevel::LEVEL_WARNING);
	}

	void info(const string &msg) {
		getLog()->log(msg, LogLevel::LEVEL_INFO);
	}

	void trace(const string &msg) {
		getLog()->log(msg, LogLevel::LEVEL_TRACE);
	}
};
