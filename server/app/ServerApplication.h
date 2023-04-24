#pragma once

#include "../../common/base/app/ApplicationAbstract.h"
#include "../../common/base/config/IniConfig.h"
#include "../../common/base/exception/ConfigException.h"
#include "../../common/base/log/ConsoleLog.h"

class ServerApplication : public virtual ApplicationAbstract {
protected:
	LogInterface *createLogger(const string &logName) {
		if (logName == "console") {
			return new ConsoleLog;
		}
		return new ConsoleLog;
	}

	IniConfig *createConfig() {
		auto *config = new IniConfig;
		config->readFile(CONFIG_FILE);
		return config;
	}

public:
	const char *CONFIG_FILE = "server.ini";

	explicit ServerApplication(function<int()> &&func) : ApplicationAbstract(std::move(func)) {
		m_config = createConfig();
		if (m_config->getRoot() == nullptr) {
			throw ConfigException("Invalid config");
		}
		if (!m_config->getRoot()->hasChild("App")) {
			throw ConfigException("Invalid config");
		}
		auto *appConfig = m_config->getRoot()->getChildById("App");
		if (!appConfig->hasChild("logName")) {
			throw ConfigException("Invalid config");
		}
		m_logger = new Logger(createLogger(appConfig->getChildById("logName")->getString()));
	}

	static ServerApplication *getApp(function<int()> &&func = {}) {
		static ServerApplication *app = nullptr;
		if (app == nullptr) {
			app = new ServerApplication(std::move(func));
		}
		return app;
	}

	int run() override {
		try {
			return m_func();
		} catch (const ExceptionBase &e) {
			ServerApplication::getLogger()->error(e.what());
		} catch (...) {
			ServerApplication::getLogger()->error("An error occurred");
		}
		return -1;
	}
};
