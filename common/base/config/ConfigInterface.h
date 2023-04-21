#pragma once

#include "setting/SettingInterface.h"

#include <fstream>
#include <string>

using namespace std;

class ConfigInterface {
public:
	virtual SettingInterface *getRoot() = 0;

	virtual bool readFile(fstream &&) = 0;

	virtual bool readFile(fstream &) = 0;

	virtual bool readFile(const string &) = 0;

	virtual bool readFile(const char *) = 0;

	virtual bool readString(const string &) = 0;

	virtual bool readString(const char *) = 0;
};
