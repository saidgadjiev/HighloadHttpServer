cmake_minimum_required(VERSION 3.3)
project(HttpServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -levent")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/said/Desktop/Study/AttempProgramming/CProject/HttpServer")

set(SOURCE_FILES main.cpp Server.cpp Server.h MimeType.cpp MimeType.h Header.h HttpResponse.cpp HttpResponse.h HttpRequest.cpp HttpRequest.h HttpRequestParser.cpp HttpRequestParser.h HttpRequestHandler.cpp HttpRequestHandler.h)
add_executable(HttpServer ${SOURCE_FILES})