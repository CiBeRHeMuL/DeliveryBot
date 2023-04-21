#pragma once

#include "ConfigInterface.h"
#include "setting/SettingAbstract.h"
#include "parser/ParserInterface.h"

#include <string>

class ConfigAbstract : public virtual ConfigInterface {
protected:
	SettingInterface *m_root = nullptr;

	ParserInterface *m_parser = nullptr;

public:
	~ConfigAbstract() {
		if (m_root != nullptr) {
			delete m_root;
			m_root = nullptr;
		}
		if (m_parser != nullptr) {
			delete m_parser;
			m_parser = nullptr;
		}
	}

	SettingInterface *getRoot() override {
		return m_root;
	}

	bool readFile(fstream &&file) override {
		if (file.is_open()) {
			string data;
			getline(file, data, '\0');
			return readString(data);
		}
		return false;
	}

	bool readFile(fstream &file) override {
		return readFile(std::move(file));
	}

	bool readFile(const string &filename) override {
		return readFile(fstream(filename));
	}

	bool readFile(const char *filename) override {
		return readFile(fstream(string(filename)));
	}

	bool readString(const char *data) override {
		return readString(string(data));
	}

	bool readString(const string &data) override {
		m_root = m_parser->parse(data);
		return m_root != nullptr;
	}
};
