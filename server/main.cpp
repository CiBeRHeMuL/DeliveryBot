#include "app/ServerApplication.h"
#include "../common/network/request/MQTTRequest.h"

#include <iostream>

using namespace std;

ServerApplication *g_application;

int loop() {
	auto *config = g_application->getConfig()->getRoot();
	config = config->getFirstChild();
	for (; config; config = config->getNext()) {
		cout << '[' << config->getStrId() << "]\n";
		for (auto *child = config->getFirstChild(); child; child = child->getNext()) {
			cout << child->getStrId() << '=' << child->getString() << '\n';
		}
	}

	auto request = MQTTRequest();
	string input;
	cin >> input;
	while(input != "exit") {
		request.setData({{"text", input}});
		request.send();
		cin >> input;
	}
	return 0;
}

int main() {
	g_application = new ServerApplication(loop);
	MosquittoPublisher::getInstance(g_application->getConfig()->getRoot()->getChildById("Mosquitto"));
	g_application->run();
	return 0;
}
