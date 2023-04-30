#include "app/ServerApplication.h"
#include "network/request/MQTTRequest.h"
#include "command/BotCommand.h"
#include "network/serialiazer/BotCommandSerializer.h"
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

	auto request = MQTTRequest<BotCommand>(new BotCommandSerializer);
	string input;
	cin >> input;
	while(input != "exit") {
		BotCommand cmd;
		cmd.setAction(BotCommand::Action::FORWARD);
		cmd.setSpeed(0.4);
		cmd.setValue(1.6);
		request.setData(cmd);
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
