//
// Created by Саид on 14.02.16.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H

#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "Workqueue.h"
#include <event2/thread.h>
#include "HttpRequestHandler.h"
#include "HttpRequestParser.h"
#include "Client.h"

namespace http {
    namespace server {
        class HttpServer
        {
        public:
            HttpServer();
            virtual ~HttpServer();
            void startServer(int port, int nCPU, char *rootDir);

        private:
            static void acceptConnCb(struct evconnlistener *listener,
                                     evutil_socket_t fd, struct sockaddr *address, int socklen,
                                     void *ctx);
            static void acceptErrorCb(struct evconnlistener *listener, void *ctx);
            static void readCb(struct bufferevent *bev, void *ctx);
            static void eventCb(struct bufferevent *bev, short events, void *ctx);
            static void serverJobFunction(struct job *job);
            static void writeCb(bufferevent *bev, void *ctx);

            static workqueue_t workqueue;
            static char *rootDir_;
        };
    }
}

#endif //HTTPSERVER_SERVER_H
