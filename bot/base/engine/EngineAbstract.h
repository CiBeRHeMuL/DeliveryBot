#pragma once

#include "../../../common/base/direction/DirectionAbstract.h"

class EngineAbstract {
public:
	virtual size_t move(int stepsCount) = 0;
};
