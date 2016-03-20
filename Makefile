all: build_server

build_server:
	g++ -std=c++11 -levent -levent_pthreads -lpthread -o server main.cpp API/Client.cpp API/Server.cpp API/Workqueue.cpp API/MimeType.cpp API/HttpResponse.cpp API/HttpRequest.cpp API/HttpRequestParser.cpp API/HttpRequestHandler.cpp

clean:
	rm -rf *.o server
