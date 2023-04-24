#pragma once

#include "InstructionAbstract.h"

class Instruction : public virtual InstructionAbstract {
public:
	Instruction() : InstructionAbstract() {}
};
