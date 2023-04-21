#include "../common/base/network/component/MosquittoSubscriber.h"
#include "app/BotApplication.h"

#include <iostream>

using namespace std;

BotApplication *g_application;

void callback(mosquitto *mosquitto, void *user, const mosquitto_message *message) {
	cout << "Message receiving from [" + string(message->topic) + "]\n";
	cout << string(static_cast<char *>(message->payload), message->payloadlen) << "\n";
}

int main() {
	g_application = new BotApplication(callback);
	g_application->run();
}
