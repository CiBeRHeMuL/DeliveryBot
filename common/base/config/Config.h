#pragma once

#include <libconfig.h++>
#include <string>

using namespace std;

class Config {
protected:
	string m_filename;

	static Config &getInstance() {
		static Config instance;
		return instance;
	}

	Config() = default;
public:
	static void setConfigFile(const string &filename) {
		Config::getInstance().m_filename = filename;
	}

	static const libconfig::Config &getConfig() {
		static libconfig::Config config;
		config.readFile(Config::getInstance().m_filename.c_str());
		return config;
	}
};
