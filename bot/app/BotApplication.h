#pragma once

#include "../../common/base/app/ApplicationAbstract.h"
#include "../../common/base/config/IniConfig.h"
#include "../../common/base/exception/ConfigException.h"
#include "../../common/base/log/ConsoleLog.h"
#include "../../common/base/network/component/MosquittoSubscriber.h"

#include <sstream>
#include <filesystem>

class BotApplication : public virtual ApplicationAbstract {
protected:
	void (*m_mosqCallback) (mosquitto *mosquitto, void *user, const mosquitto_message *message);

	MosquittoSubscriber *m_mosqSubscriber;

	LogInterface *createLogger(const string &logName) {
		if (logName == "console") {
			return new ConsoleLog;
		}
		return new ConsoleLog;
	}

	IniConfig *createConfig() {
		auto *config = new IniConfig;
		config->readFile(filesystem::current_path().c_str() + string(CONFIG_FILE));
		return config;
	}

public:
	const char *CONFIG_FILE = "/bot.ini";

	explicit BotApplication(void (*callback) (mosquitto *mosquitto, void *user, const mosquitto_message *message)) : m_mosqCallback(callback)
	{
		m_config = createConfig();
		if (m_config->getRoot() == nullptr) {
			throw ConfigException("Config not set");
		}
		m_logger = new Logger(createLogger(m_config->getRoot()->getChildById("App")->getChildById("logName")->getString()));
		m_mosqSubscriber = new MosquittoSubscriber(m_config->getRoot()->getChildById("Mosquitto"), m_mosqCallback);
		m_mosqSubscriber->init();
	}

	~BotApplication() {
		delete m_mosqSubscriber;
		m_mosqSubscriber = nullptr;
	}

	static BotApplication *getApp(void (*callback) (mosquitto *mosquitto, void *user, const mosquitto_message *message) = nullptr) {
		static BotApplication *app = nullptr;
		if (app == nullptr) {
			if (callback == nullptr) {
				throw ConfigException("Cannot initialize bot application without callback");
			}
			app = new BotApplication(callback);
		}
		return app;
	}

	int run() override {
		try {
			m_mosqSubscriber->startListen();
			while (m_mosqSubscriber->isListening()) {}
			return 0;
		} catch (const ExceptionBase &e) {
			BotApplication::getLogger()->error(e.what());
		} catch (...) {
			BotApplication::getLogger()->error("An error occurred");
		}
		return -1;
	}
};
