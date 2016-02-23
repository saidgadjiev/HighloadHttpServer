#include "Server.h"

using namespace http::server;

int main() {
    //Server server(8000);

    //server.start();

    char data[8192] = "GET / HTTP/1.1\r\n"
            "Host: localhost:8000\r\n\r\n";

    HttpRequest request;
    HttpRequestParser requestParser;
    requestParser.reset();

    requestParser.parse(request, data, 431);

    return 0;
}