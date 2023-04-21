#pragma once

#include "ParserInterface.h"

class ParserAbstract : public virtual ParserInterface {
public:
	SettingInterface *parse(const std::string &data) override {
		return nullptr;
	}
};
