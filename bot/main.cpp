#include "../common/base/network/component/MosquittoSubscriber.h"
#include "app/BotApplication.h"

#include <iostream>

using namespace std;

BotApplication *app;

void callback(BotCommand &cmd) {
	app->getLogger()->info(cmd.toQueryString());
}

int main() {
	app = BotApplication::getApp(callback);
	return app->run();
}
