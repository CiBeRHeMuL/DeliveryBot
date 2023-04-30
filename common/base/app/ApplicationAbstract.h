#pragma once

#include "ApplicationInterface.h"
#include "../config/ConfigInterface.h"
#include "../log/Logger.h"
#include "../exception/ExceptionBase.h"

class ApplicationAbstract : public virtual ApplicationInterface {
protected:
	Logger *m_logger;

	ConfigInterface *m_config;

	function<int()> m_func;

public:
	ApplicationAbstract(function<int()> &&func) : ApplicationInterface(), m_func(func) {}

	ApplicationAbstract() : ApplicationInterface(), m_func() {}

	~ApplicationAbstract() {
		if (m_logger != nullptr) {
			delete m_logger;
			m_logger = nullptr;
		}
		if (m_config != nullptr) {
			delete m_config;
			m_config = nullptr;
		}
	}

	int run() override {
		try {
			return m_func();
		} catch (const ExceptionBase &ex) {
			m_logger->error(ex.what());
		} catch (...) {
			m_logger->error("An error occurred");
		}
		return -1;
	}

	ConfigInterface *getConfig() {
		return m_config;
	}

	Logger *getLogger() {
		return m_logger;
	}
};
