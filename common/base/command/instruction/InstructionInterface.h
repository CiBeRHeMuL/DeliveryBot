#pragma once

#include "InstructionType.h"
#include "InstructionIdType.h"

#include <string>
#include <vector>
#include <map>

using namespace std;

class InstructionInterface {
public:
	~InstructionInterface() = default;

	virtual void setName(const string &) = 0;

	virtual string getName() = 0;

	virtual InstructionIdType::Type getIdType() = 0;

	virtual InstructionType::Type getType() = 0;

	virtual void setString(const string &) = 0;

	virtual string getString() = 0;

	virtual explicit inline operator string() = 0;

	virtual void addChild(InstructionInterface *) = 0;

	virtual void addChildren(vector<InstructionInterface *> &) = 0;

	virtual InstructionInterface *getChild(int) = 0;

	virtual InstructionInterface *getChild(const string &) = 0;

	virtual vector<InstructionInterface *> &getChildren() = 0;

	virtual inline InstructionInterface &operator[](int) = 0;

	virtual inline InstructionInterface &operator[](const string &) = 0;

	virtual string toQueryString(bool, bool) = 0;
};
