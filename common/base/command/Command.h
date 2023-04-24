#pragma once

#include "CommandAbstract.h"

class Command : public virtual CommandAbstract {
public:
	Command() : CommandAbstract() {}
};
