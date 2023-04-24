#pragma once

#include "InstructionInterface.h"
#include "InstructionType.h"
#include "InstructionIdType.h"
#include "../../exception/InstructionException.h"

#include <sstream>

class InstructionAbstract : public InstructionInterface {
protected:
	string m_name;
	InstructionIdType::Type m_idType = InstructionIdType::TYPE_ID;
	
	string m_stringValue;
	vector<InstructionInterface *> m_children;
	InstructionType::Type m_type = InstructionType::TYPE_NONE;

public:
	InstructionAbstract() : InstructionInterface() {}

	explicit InstructionAbstract(InstructionAbstract *other) {
		m_idType = other->getIdType();
		if (m_idType == InstructionIdType::TYPE_NAME) {
			m_name = other->getName();
		}

		m_type = other->getType();
		switch (m_type) {
			case InstructionType::TYPE_STRING:
				m_stringValue = other->getString();
				break;
			case InstructionType::TYPE_GROUP:
				for (auto *el : other->getChildren()) {
					m_children.emplace_back(el);
				}
			default:
				break;
		}
	}

	~InstructionAbstract() {
		m_children.clear();
	}

	void setName(const string &name) override {
		m_name = name;
		m_idType = InstructionIdType::TYPE_NAME;
	}

	string getName() override {
		return m_name;
	}

	InstructionIdType::Type getIdType() override {
		return m_idType;
	}

	InstructionType::Type getType() override {
		return m_type;
	}

	void setString(const string &value) override {
		m_stringValue = value;
		m_type = InstructionType::TYPE_STRING;
	}

	string getString() override {
		if (m_type == InstructionType::TYPE_STRING) {
			return m_stringValue;
		}
		throw InstructionException("Cannot get string value from non string instruction");
	}

	explicit inline operator string() override {
		return getString();
	}

	void addChild(InstructionInterface *child) override {
		erase_if(m_children, [&] (InstructionInterface *el) {
			return el->getIdType() == InstructionIdType::TYPE_NAME
				&& child->getIdType() == InstructionIdType::TYPE_NAME
				&& el->getName() == child->getName();
		});
		m_children.emplace_back(child);
		m_type = InstructionType::TYPE_GROUP;
	}

	void addChildren(vector<InstructionInterface *> &children) override {
		for (auto *el : children) {
			addChild(el);
		}
	}

	InstructionAbstract *getChild(int index) override {
		if (m_type == InstructionType::TYPE_GROUP) {
			int i = 0;
			for (auto &el : m_children) {
				if (el->getIdType() == InstructionIdType::TYPE_ID) {
					if (i == index) {
						return dynamic_cast<InstructionAbstract*>(el);
					}
					++i;
				}
			}
			throw InstructionException("Getting unknown children with index = " + to_string(index));
		}
		throw InstructionException("Cannot get child of string instruction");
	}

	InstructionInterface *getChild(const string &name) override {
		if (m_type == InstructionType::TYPE_GROUP) {
			auto it = m_children.begin();
			if ((it = std::find_if(m_children.begin(), m_children.end(), [&] (InstructionInterface *el) -> bool {
				return el->getIdType() == InstructionIdType::TYPE_NAME && name == el->getName();
			})) != m_children.end()) {
				return *it;
			}
			throw InstructionException("Getting unknown children with name = " + name);
		}
		throw InstructionException("Cannot get child of string instruction");
	}

	vector<InstructionInterface *> &getChildren() override {
		if (m_type == InstructionType::TYPE_GROUP) {
			return m_children;
		}
		throw InstructionException("Cannot get children from non group instruction");
	}

	inline InstructionInterface &operator[](int index) override {
		return *getChild(index);
	}

	inline InstructionInterface &operator[](const string &name) override {
		return *getChild(name);
	}

	string toQueryString(bool asRoot = false, bool separateByLine = false) override {
		if (m_type == InstructionType::TYPE_STRING) {
			if (m_idType == InstructionIdType::TYPE_NAME) {
				return asRoot ? m_name + "=" + m_stringValue : "[" + m_name + "]=" + m_stringValue;
			} else {
				return asRoot ? m_stringValue : "[]=" + m_stringValue;
			}
		} else if (m_type == InstructionType::TYPE_GROUP) {
			string result;
			for (auto* el : m_children) {
				string subResult;
				if (m_idType == InstructionIdType::TYPE_NAME) {
					subResult += asRoot ? "" : "[" + m_name + "]";
				} else {
					subResult += asRoot ? "" : "[]";
				}
				subResult += el->toQueryString(false, separateByLine) + (separateByLine ? "\n" : "&");
				if (asRoot) {
					subResult.pop_back();
					stringstream ss(subResult);
					while (!ss.eof()) {
						string datum;
						getline(ss, datum, '\n');
						result += m_name + datum + '\n';
					}
				} else {
					result += subResult;
				}
			}
			result.pop_back();
			return result;
		}
		return "";
	}
};
