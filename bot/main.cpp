#include "../common/base/network/component/MosquittoSubscriber.h"
#include "app/BotApplication.h"

#include <iostream>

using namespace std;

BotApplication *app;

void callback(mosquitto *mosquitto, void *user, const mosquitto_message *message) {
	app->getLogger()->info(string(reinterpret_cast<char *>(message->payload), message->payloadlen));
}

int main() {
	app = BotApplication::getApp(callback);
	return app->run();
}
