#pragma once

#include "CommandAbstract.h"

class BotCommand : public virtual CommandAbstract {
public:
	BotCommand() : CommandAbstract() {}

	void setAction(const string &action) {
		CommandAbstract::setInstruction("action", action);
	}
};
