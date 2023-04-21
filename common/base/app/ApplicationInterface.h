#pragma once

#include <functional>

using namespace std;

class ApplicationInterface {
public:
	~ApplicationInterface() = default;

	virtual int run() = 0;
};
