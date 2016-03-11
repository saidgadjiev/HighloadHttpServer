#include <iostream>
//#include "API/Server.h"
#include "API/Workqueue.h"
using namespace http::server;

int main() {
	//Server server(8000, 1);

	//server.start();
	Workqueue workqueue;

	workqueue.init(1);
	workqueue.shutdown();

	return 0;
}