#include "app/ServerApplication.h"
#include "network/request/MQTTRequest.h"
#include "../common/base/command/BotCommand.h"
#include "network/serialiazer/CommandSerializer.h"
#include "network/component/ServerMosquittoPublisher.h"

#include <iostream>

using namespace std;

ServerApplication *app;

int loop() {
	auto *config = app->getConfig()->getRoot();
	config = config->getFirstChild();
	for (; config; config = config->getNext()) {
		cout << '[' << config->getStrId() << "]\n";
		for (auto *child = config->getFirstChild(); child; child = child->getNext()) {
			cout << child->getStrId() << '=' << child->getString() << '\n';
		}
	}

	auto request = MQTTRequest<BotCommand *>(reinterpret_cast<SerializerInterface<BotCommand*>*>(new CommandSerializer));
	string input;
	cin >> input;
	while(input != "exit") {
		BotCommand cmd;
		cmd.setAction("move");
		cmd.setInstruction("statuses[steps][x]", "10");
		cmd.setInstruction("statuses[steps][y]", "20");
		request.setData(&cmd);
		request.send();
		app->getLogger()->warning(to_string(ServerMosquittoPublisher::getInstance()->getLastResult()));
		cin >> input;
	}
	return 0;
}

int main() {
	app = ServerApplication::getApp(loop);
	ServerMosquittoPublisher::getInstance(app->getConfig()->getRoot()->getChildById("Mosquitto"));
	return app->run();
}
