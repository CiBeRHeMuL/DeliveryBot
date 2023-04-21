#pragma once

#include "../setting/SettingInterface.h"

#include <string>

using namespace std;

class ParserInterface {
public:
	virtual SettingInterface *parse(const string &data) = 0;

	virtual ~ParserInterface() = default;
};
