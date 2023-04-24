#pragma once

#include <string>
#include <vector>
#include "../exception/BotCommandException.h"

using namespace std;

class BotCommand {
public:
	class Action {
	public:
		const static string FORWARD;
		const static string LEFT;
		const static string RIGHT;
		const static string BACK;
		const static string STOP;

		static vector<string> getList() {
			static vector<string> list = {FORWARD, LEFT, RIGHT, BACK, STOP};
			return list;
		}
	};

protected:
	string m_action;
	double m_speed;
	double m_value;

public:
	string getAction() const {
		return m_action;
	}

	void setAction(const string& action) {
		auto list = Action::getList();
		if (find(list.begin(), list.end(), action) == list.end()) {
			throw BotCommandException("Invalid action");
		}
		m_action = action;
	}

	double getSpeed() const {
		return m_speed;
	}

	void setSpeed(double speed) {
		if (speed < 0 || speed > 1.0) {
			throw BotCommandException("Invalid speed");
		}
		m_speed = speed;
	}

	double getValue() const {
		return m_value;
	}

	void setValue(double value) {
		m_value = value;
	}
};

const string BotCommand::Action::FORWARD = "forward";
const string BotCommand::Action::LEFT = "left";
const string BotCommand::Action::RIGHT = "right";
const string BotCommand::Action::BACK = "back";
const string BotCommand::Action::STOP = "stop";
