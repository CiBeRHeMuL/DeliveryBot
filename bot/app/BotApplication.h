#pragma once

#include "../../common/base/app/ApplicationAbstract.h"
#include "../../common/base/config/IniConfig.h"
#include "../../common/base/exception/ConfigException.h"
#include "../../common/base/log/ConsoleLog.h"
#include "../../common/base/network/component/MosquittoSubscriber.h"
#include "../../common/base/command/BotCommand.h"

#include <sstream>
#include <filesystem>

class BotApplication : public virtual ApplicationAbstract {
protected:
	function<void(BotCommand &)> m_callback;

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

	static void baseMosquittoCallback(mosquitto *mosquitto, void *user, const mosquitto_message *message) {
		stringstream ss(string(reinterpret_cast<char *>(message->payload), message->payloadlen));
		BotCommand cmd;
		string a(reinterpret_cast<char *>(message->payload), message->payloadlen);

		string key;
		string data;
		while (!ss.eof()) {
			getline(ss, key, '=');
			getline(ss, data, '\n');
			cmd.setInstruction(key, data);
		}
		auto *app = BotApplication::getApp();
		app->m_callback(cmd);
	}

public:
	const char *CONFIG_FILE = "/bot.ini";

	explicit BotApplication(function<void(BotCommand &)> &&func) : m_callback(std::move(func))
	{
		m_config = createConfig();
		if (m_config->getRoot() == nullptr) {
			throw ConfigException("Config not set");
		}
		m_logger = new Logger(createLogger(m_config->getRoot()->getChildById("App")->getChildById("logName")->getString()));
		m_mosqSubscriber = new MosquittoSubscriber(m_config->getRoot()->getChildById("Mosquitto"), baseMosquittoCallback);
		m_mosqSubscriber->init();
	}

	~BotApplication() {
		delete m_mosqSubscriber;
		m_mosqSubscriber = nullptr;
	}

	static BotApplication *getApp(function<void(BotCommand &)> &&func = {}) {
		static BotApplication *app = nullptr;
		if (app == nullptr) {
			app = new BotApplication(std::move(func));
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
