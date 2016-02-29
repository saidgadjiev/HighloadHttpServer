#include "Server.h"

using namespace http::server;

int main() {
	Server server(8000);

	server.start();

	return 0;
}