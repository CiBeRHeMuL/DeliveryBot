#pragma once

#include <string>

using namespace std;

class SettingInterface {
public:
	virtual ~SettingInterface() = default;

	virtual int getIntId() = 0;

	virtual string getStrId() = 0;

	virtual bool isRoot() = 0;

	virtual SettingInterface *getParent() = 0;

	virtual SettingInterface *getNext() = 0;

	virtual SettingInterface *getPrev() = 0;

	virtual SettingInterface *getFirstChild() = 0;

	virtual SettingInterface *getChildById(int) = 0;

	virtual SettingInterface *getChildById(const string &) = 0;

	virtual SettingInterface *getChildById(const char *) = 0;

	virtual bool getBool() = 0;

	virtual int getInt() = 0;

	virtual unsigned int getUInt() = 0;

	virtual long getLong() = 0;

	virtual unsigned long getULong() = 0;

	virtual long long getLLong() = 0;

	virtual unsigned long long getULLong() = 0;

	virtual float getFloat() = 0;

	virtual double getDouble() = 0;

	virtual long double getLDouble() = 0;

	virtual explicit operator bool() = 0;

	virtual explicit operator int() = 0;

	virtual explicit operator unsigned int() = 0;

	virtual explicit operator long() = 0;

	virtual explicit operator unsigned long() = 0;

	virtual explicit operator long long() = 0;

	virtual explicit operator unsigned long long() = 0;

	virtual explicit operator float() = 0;

	virtual explicit operator double() = 0;

	virtual explicit operator long double() = 0;

	virtual explicit operator string() = 0;

	virtual string getString() = 0;

	virtual bool hasChild(int) = 0;

	virtual bool hasChild(const string &) = 0;

	virtual bool hasChild(const char *) = 0;

	virtual SettingInterface &operator[](int) = 0;

	virtual SettingInterface &operator[](const string &) = 0;

	virtual SettingInterface &operator[](const char *) = 0;
};
