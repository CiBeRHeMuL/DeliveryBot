#pragma once

#include "../../../common/base/command/CommandInterface.h"
#include "../../../common/base/network/serializer/SerializerAbstract.h"

class CommandSerializer : public virtual SerializerAbstract<CommandInterface *> {
public:
	string serialize(CommandInterface *const &data) override {
		if (data == nullptr) {
			return "";
		}
		return data->toQueryString();
	}
};
