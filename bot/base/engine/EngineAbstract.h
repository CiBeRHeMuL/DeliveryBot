#pragma once

#include "../../../common/base/direction/DirectionAbstract.h"

class EngineAbstract {
public:
	virtual size_t move(const DirectionAbstract &, size_t stepsCount) = 0;
};
