#pragma once

#include "../../../common/base/network/serializer/SerializerAbstract.h"
#include "../../command/BotCommand.h"

#include <nlohmann/json.hpp>

using namespace nlohmann;

class BotCommandSerializer : public virtual SerializerAbstract<BotCommand> {
public:
	string serialize(const BotCommand& data) override {
		json json = {
			{"cmd", data.getAction()},
			{"value", data.getValue()},
			{"spd", data.getSpeed()},
		};
		return json.dump();
	}
};
