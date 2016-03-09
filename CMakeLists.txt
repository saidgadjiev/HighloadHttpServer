cmake_minimum_required(VERSION 3.3)
project(HttpServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -levent")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/said/Desktop/Study/AttempProgramming/CProject/HttpServer")

set(SOURCE_FILES main.cpp API/Server.cpp API/Server.h API/MimeType.cpp API/MimeType.h API/NameValue.h API/HttpResponse.cpp
        API/HttpResponse.h API/HttpRequest.cpp API/HttpRequest.h API/HttpRequestParser.cpp API/HttpRequestParser.h
        API/HttpRequestHandler.cpp API/HttpRequestHandler.h API/NameValue.h API/WorkQueue.cpp API/WorkQueue.h)
add_executable(HttpServer ${SOURCE_FILES})