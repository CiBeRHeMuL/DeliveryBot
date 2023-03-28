#pragma once

#include "../exception/DirectionException.h"

#include <string>

using namespace std;

class DirectionAbstract {
public:
	virtual size_t getXSteps() = 0;

	virtual size_t getYSteps() = 0;

	static DirectionAbstract &fromString() {
		throw DirectionException("This method must be implemented");
	}

	static void toString() {
		throw DirectionException("This method must be implemented");
	}
};
