#pragma once

#include "ParserAbstract.h"
#include "../setting/IniSetting.h"
#include "../../exception/InvalidConfigException.h"

#include <sstream>
#include <string>

using namespace std;

class IniParser : public virtual ParserAbstract {
protected:
	static IniSetting *createSetting(const string &line) {
		auto *elem = new IniSetting;
		elem->m_idType = TYPE_ID_STRING;
		if (line[0] == '[' && line[line.size() - 1] == ']') {
			elem->m_strId = line.substr(1, line.size() - 2);
			elem->m_type = SettingType::TYPE_LIST;
			elem->m_level = 1;
		} else if (line.find('=') != line.size()) {
			elem->m_strId = line.substr(0, line.find('='));
			string value = line.substr(line.find('=') + 1);
			elem->m_level = 2;
			if (value == "true" || value == "false") {
				elem->m_boolValue = value == "true";
				elem->m_type = SettingType::TYPE_BOOL;
			}
			try {
				elem->m_floatValue = stof(value);
				elem->m_type = SettingType::TYPE_FLOAT;
				return elem;
			} catch (...) {}
			try {
				elem->m_doubleValue = stod(value);
				elem->m_type = SettingType::TYPE_DOUBLE;
				return elem;
			} catch (...) {}
			try {
				elem->m_lDoubleValue = stold(value);
				elem->m_type = SettingType::TYPE_LONG_DOUBLE;
				return elem;
			} catch (...) {}
			try {
				elem->m_intValue = stoi(value);
				elem->m_type = SettingType::TYPE_INT;
				return elem;
			} catch (...) {}
			try {
				elem->m_longValue = stol(value);
				elem->m_type = SettingType::TYPE_LONG;
				return elem;
			} catch (...) {}
			try {
				elem->m_uLongValue = stoul(value);
				elem->m_type = SettingType::TYPE_ULONG;
				return elem;
			} catch (...) {}
			try {
				elem->m_lLongValue = stoll(value);
				elem->m_type = SettingType::TYPE_LONG_LONG;
				return elem;
			} catch (...) {}
			try {
				elem->m_uLLongValue = stoull(value);
				elem->m_type = SettingType::TYPE_ULONG_LONG;
				return elem;
			} catch (...) {}
			elem->m_type = SettingType::TYPE_STRING;
			elem->m_stringValue = value;
		} else {
			throw InvalidConfigException("Invalid syntax");
		}
		return elem;
	}

public:
	IniSetting *parse(const std::string &data) override {
		stringstream ss(data);
		string line;
		auto *root = new IniSetting;
		root->m_type = SettingType::TYPE_LIST;
		IniSetting *currentParent = root;
		IniSetting *prevElem = root;
		while (!ss.eof()) {
			ss >> line;
			if (line.empty()) {
				continue;
			}

			IniSetting *elem = createSetting(line);

			if (prevElem->m_level == elem->m_level) {
				elem->m_prev = prevElem;
				prevElem->m_next = elem;
			} else if (elem->m_level > prevElem->m_level) {
				if (currentParent->m_firstChild == nullptr) {
					currentParent->m_firstChild = elem;
				}
			} else {
				prevElem = currentParent;
				currentParent = dynamic_cast<IniSetting *>(currentParent->m_parent);
				prevElem->m_next = elem;
				elem->m_prev = currentParent;
			}
			elem->m_parent = currentParent;
			prevElem = elem;

			if (elem->m_type == SettingType::TYPE_LIST || elem->m_type == SettingType::TYPE_ARRAY) {
				currentParent = elem;
			}
		}
		return root;
	}
};
