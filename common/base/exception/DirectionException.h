#pragma once

#include <exception>

using namespace std;

class DirectionException : public exception {
public:
	DirectionException(const char *msg) : exception(msg) {}
};
