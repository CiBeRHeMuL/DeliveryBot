#pragma once

#include "ParserInterface.h"

template<class T>
class ParserAbstract : public virtual ParserInterface<T> {
public:
	T parse(const string &str) {
		return {};
	}
};
