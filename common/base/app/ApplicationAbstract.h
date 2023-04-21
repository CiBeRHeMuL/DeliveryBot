#pragma once

#include "ApplicationInterface.h"
#include "../config/ConfigInterface.h"
#include "../log/Logger.h"

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
		return 0;
	}

	ConfigInterface *getConfig() {
		return m_config;
	}

	Logger *getLogger() {
		return m_logger;
	}
};
