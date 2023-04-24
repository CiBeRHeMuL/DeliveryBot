#pragma once

#include "SettingInterface.h"
#include "SettingType.h"
#include "SettingIdType.h"
#include "../../exception/WrongSettingTypeException.h"
#include "../../exception/WrongTypeConversionException.h"
#include "../../exception/ConfigException.h"

#include <limits>
#include <sstream>
#include <string>

using namespace std;

class SettingAbstract : public virtual SettingInterface {
protected:
	SettingAbstract* m_parent = nullptr;
	SettingAbstract* m_firstChild = nullptr;
	SettingAbstract* m_next = nullptr;
	SettingAbstract* m_prev = nullptr;

	unsigned int m_level = 0;

	SettingIdType m_idType = SettingIdType::TYPE_ID_INT;

	string m_strId;
	int m_intId;

	SettingType::Type m_type = SettingType::TYPE_NONE;

	bool m_boolValue;
	int m_intValue;
	unsigned int m_uIntValue;
	long m_longValue;
	unsigned long m_uLongValue;
	long long m_lLongValue;
	unsigned long long m_uLLongValue;
	float m_floatValue;
	double m_doubleValue;
	long double m_lDoubleValue;
	string  m_stringValue;

	template<class From, class To>
	To convertValue(From val) {
		if constexpr (is_same_v<From, To>) {
			return val;
		}
		if constexpr (
			is_convertible_v<From, To>
			&& (is_arithmetic_v<From> || is_same_v<From, bool>)
			&& (is_arithmetic_v<To> || is_same_v<To, bool>)
			&& !is_same_v<From, To>
		) {
			if constexpr (is_same_v<To, bool>) {
				return static_cast<bool>(val);
			} else {
				if (val >= numeric_limits<To>::min() && val <= numeric_limits<To>::max()) {
					return static_cast<To>(val);
				}
				throw WrongTypeConversionException(typeid(From).name(), typeid(To).name());
			}
		} else if constexpr (
			is_same_v<From, string>
			&& (is_arithmetic_v<To> || is_same_v<To, bool>)
			&& !is_same_v<From, To>
		) {
			stringstream ss(val);
			To result{};
			try {
				ss >> result;
				return result;
			} catch (...) {
				if constexpr (is_same_v<To, bool>) {
					if (val == "true") {
						return true;
					} else if (val == "false") {
						return false;
					}
				}
				throw WrongTypeConversionException(typeid(From).name(), typeid(To).name());
			}
		} else if constexpr (
			is_same_v<To, string>
			&& (is_arithmetic_v<From> || is_same_v<From, bool>)
			&& !is_same_v<From, To>
		) {
			if constexpr (is_same_v<From, bool>) {
				return val ? "true" : "false";
			} else {
				return to_string(val);
			}
		}
	}

	template<class To>
	To convertTo() {
		switch (m_type) {
			case SettingType::TYPE_INT:
				return convertValue<int, To>(m_intValue);
			case SettingType::TYPE_UINT:
				return convertValue<unsigned int, To>(m_uIntValue);
			case SettingType::TYPE_LONG:
				return convertValue<long, To>(m_longValue);
			case SettingType::TYPE_ULONG:
				return convertValue<unsigned long, To>(m_uLongValue);
			case SettingType::TYPE_LONG_LONG:
				return convertValue<long long, To>(m_lLongValue);
			case SettingType::TYPE_ULONG_LONG:
				return convertValue<unsigned long long, To>(m_uLLongValue);
			case SettingType::TYPE_BOOL:
				return convertValue<bool, To>(m_boolValue);
			case SettingType::TYPE_FLOAT:
				return convertValue<float, To>(m_floatValue);
			case SettingType::TYPE_DOUBLE:
				return convertValue<double, To>(m_doubleValue);
			case SettingType::TYPE_LONG_DOUBLE:
				return convertValue<long double, To>(m_lDoubleValue);
			case SettingType::TYPE_STRING:
				return convertValue<string, To>(m_stringValue);
			default:
				throw WrongTypeConversionException(SettingType::getTypeName(m_type), "int");
		}
	}

public:
	~SettingAbstract() override {
		if (m_next != nullptr) {
			delete m_next;
			m_next = nullptr;
		}
		if (m_firstChild != nullptr) {
			delete m_firstChild;
			m_firstChild = nullptr;
		}
	}

	int getIntId() override {
		if (m_idType == TYPE_ID_INT) {
			return m_intId;
		}
		throw ConfigException("Cannot get int id of setting");
	}

	string getStrId() override {
		if (m_idType == TYPE_ID_STRING) {
			return m_strId;
		}
		throw ConfigException("Cannot get string id of setting");
	}

	bool isRoot() override {
		return m_parent == nullptr && m_level == 0u;
	}

	SettingInterface* getParent() override {
		return m_parent;
	}

	SettingInterface* getNext() override {
		return m_next;
	}

	SettingInterface* getPrev() override {
		return m_prev;
	}

	SettingInterface* getFirstChild() override {
		return m_firstChild;
	}

	SettingInterface* getChildById(int id) override {
		if (m_type == SettingType::TYPE_ARRAY) {
			for (auto child = m_firstChild; child != nullptr; child = child->m_next) {
				if (child->m_idType == SettingIdType::TYPE_ID_INT && child->m_intId == id) {
					return child;
				}
			}
		}
		return nullptr;
	}

	SettingInterface* getChildById(const string& id) override {
		if (m_type == SettingType::TYPE_LIST) {
			for (auto child = m_firstChild; child != nullptr; child = child->m_next) {
				if (child->m_idType == SettingIdType::TYPE_ID_STRING && child->m_strId == id) {
					return child;
				}
			}
		}
		return nullptr;
	}

	SettingInterface* getChildById(const char* id) override {
		return getChildById(string(id));
	}

	bool getBool() override {
		return convertTo<bool>();
	}

	int getInt() override {
		return convertTo<int>();
	}

	unsigned int getUInt() override {
		return convertTo<unsigned int>();
	}

	long getLong() override {
		return convertTo<long>();
	}

	unsigned long getULong() override {
		return convertTo<unsigned long>();
	}

	long long getLLong() override {
		return convertTo<long long>();
	}

	unsigned long long getULLong() override {
		return convertTo<unsigned long long>();
	}

	float getFloat() override {
		return convertTo<float>();
	}

	double getDouble() override {
		return convertTo<double>();
	}

	long double getLDouble() override {
		return convertTo<long double>();
	}

	string getString() override {
		return convertTo<string>();
	}

	explicit operator bool() override {
		return getBool();
	}

	explicit operator int() override {
		return getInt();
	}

	explicit operator unsigned int() override {
		return getUInt();
	}

	explicit operator long() override {
		return getLong();
	}

	explicit operator unsigned long() override {
		return getULong();
	}

	explicit operator long long() override {
		return getLLong();
	}

	explicit operator unsigned long long() override {
		return getULLong();
	}

	explicit operator float() override {
		return getFloat();
	}

	explicit operator double() override {
		return getDouble();
	}

	explicit operator long double() override {
		return getLDouble();
	}

	explicit operator string() override {
		return getString();
	}

	bool hasChild(int id) override {
		return getChildById(id) != nullptr;
	}

	bool hasChild(const string &id) override {
		return getChildById(id) != nullptr;
	}

	bool hasChild(const char *id) override {
		return hasChild(string(id));
	}

	SettingInterface &operator[](int id) override {
		auto *ptr = getChildById(id);
		if (ptr != nullptr) {
			return *ptr;
		}
		throw ConfigException("Getting unknown child by id = " + to_string(id));
	}

	SettingInterface &operator[](const string &id) override {
		auto *ptr = getChildById(id);
		if (ptr != nullptr) {
			return *ptr;
		}
		throw ConfigException("Getting unknown child by id = " + id);
	}

	SettingInterface &operator[](const char *id) override {
		return operator[](string(id));
	}
};
