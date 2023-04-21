#pragma once

#include "../../common/base/app/ApplicationAbstract.h"
#include "../../common/base/config/IniConfig.h"
#include "../../common/base/exception/ConfigException.h"
#include "../../common/base/log/ConsoleLog.h"
#include "../../common/base/network/component/MosquittoSubscriber.h"

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
		config->readFile(CONFIG_FILE);
		return config;
	}

public:
	const char *CONFIG_FILE = "bot.ini";

	explicit BotApplication(void (*func) (mosquitto *mosquitto, void *user, const mosquitto_message *message)) : m_mosqCallback(func)
	{
		m_config = createConfig();
		if (m_config->getRoot() == nullptr) {
			throw ConfigException("Invalid config");
		}
		m_logger = new Logger(createLogger(m_config->getRoot()->getChildById("App")->getChildById("logName")->getString()));
		m_mosqSubscriber = new MosquittoSubscriber(m_config->getRoot()->getChildById("Mosquitto"), m_mosqCallback);
	}

	~BotApplication() {
		delete m_mosqSubscriber;
		m_mosqSubscriber = nullptr;
		m_mosqCallback = nullptr;
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
