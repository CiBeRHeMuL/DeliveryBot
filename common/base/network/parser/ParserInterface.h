#pragma once

#include <string>

using namespace std;

template<class T>
class ParserInterface {
public:
	virtual T parse(const string &str) = 0;
};
