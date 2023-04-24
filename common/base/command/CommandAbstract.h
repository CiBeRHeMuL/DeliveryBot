#pragma once

#include "CommandInterface.h"
#include "instruction/Instruction.h"

#include <regex>

class CommandAbstract : public virtual CommandInterface {
public:
	const string KEY_REGEX = R"([^\[\]]+(\[([^\[\]]*)\])*)";
	const string SUB_KEY_REGEX = R"(\[([^\[\]]*)\])";

protected:
	Instruction *m_root;

	bool checkKey(const string &key) {
		return regex_match(key, regex(KEY_REGEX));
	}

	vector<string> getPathsFromKey(string key) {
		vector<string> paths;
		smatch matches;
		while (regex_search(key, matches, regex(SUB_KEY_REGEX))) {
			paths.push_back(matches[1].str());
			key = matches.suffix().str();
		}
		return paths;
	}

	Instruction *createChild(const string &key) {
		if (all_of(key.begin(), key.end(), [] (auto c) { return std::isalpha(c); })) {
			auto child = new Instruction;
			child->setName(key);
			m_root->addChild(child);
			return child;
		} else {
			Instruction *child;
			try {
				child = dynamic_cast<Instruction*>(m_root->getChild(key.substr(0, key.find('['))));
			} catch (...) {
				child = new Instruction;
				child->setName(key.substr(0, key.find('[')));
				m_root->addChild(child);
			}
			auto paths = getPathsFromKey(key);
			for (const auto &path : paths) {
				Instruction *subChild;
				if (!path.empty()) {
					try {
						subChild = dynamic_cast<Instruction*>(child->getChild(path));
					} catch (...) {
						subChild = new Instruction;
						subChild->setName(path);
						child->addChild(subChild);
					}
				} else {
					subChild = new Instruction;
					child->addChild(subChild);
				}
				child = subChild;
			}
			return child;
		}
	}

public:
	CommandAbstract() : CommandInterface(), m_root(new Instruction) {}

	void setInstruction(const string &key, const string &data) override {
		if (checkKey(key)) {
			auto child = createChild(key);
			child->setString(data);
		} else {
			throw InstructionException("Invalid key");
		}
	}

	string toQueryString() const override {
		string queryString;
		for (auto &child : m_root->getChildren()) {
			queryString += child->toQueryString(true, true) + "\n";
		}
		queryString.pop_back();
		return queryString;
	}

	Instruction &getInstruction(const string &key) {
		if (all_of(key.begin(), key.end(), [] (auto c) { return std::isalpha(c); })) {
			return *(dynamic_cast<Instruction *>(m_root->getChild(key)));
		}
		throw InstructionException("Invalid key");
	}
};
