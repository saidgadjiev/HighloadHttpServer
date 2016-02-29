all: build_server

build_server:
	g++ -std=c++11 -levent -o server main.cpp Server.cpp MimeType.cpp HttpResponse.cpp HttpRequest.cpp HttpRequestParser.cpp HttpRequestHandler.cpp

clean:
	rm -rf *.o server
