cmake_minimum_required(VERSION 3.3)
project(HttpServer)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -levent -lpthread -levent_pthreads")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/Users/said/Desktop/Study/AttempProgramming/CProject/HttpServer")

set(SOURCE_FILES main.cpp API/Server.cpp API/Server.h API/MimeType.cpp API/MimeType.h API/PairNameValue.h API/HttpResponse.cpp
        API/HttpResponse.h API/HttpRequest.cpp API/HttpRequest.h API/HttpRequestParser.cpp API/HttpRequestParser.h
        API/HttpRequestHandler.cpp API/HttpRequestHandler.h API/Workqueue.cpp API/Workqueue.h API/PairNameValue.h API/DateTimeHelper.h)
add_executable(HttpServer ${SOURCE_FILES})