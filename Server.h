//
// Created by Саид on 14.02.16.
//

#ifndef HTTPSERVER_SERVER_H
#define HTTPSERVER_SERVER_H

#include <easylogging++.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include "HttpResponse.h"
#include "HttpRequest.h"
#include "MimeType.h"
#include "HttpRequestParser.h"

namespace http {
    namespace server {
        class Server {
        public:
            Server(int port);
            ~Server() { }

            void start();
            void accept_conn_cb(struct evconnlistener* listener,
                                       evutil_socket_t fd,
                                       struct sockaddr* address,
                                       int socklen,
                                       void *ctx);
            void read_cb(struct bufferevent *bev, void *ctx);
            void event_cb(struct bufferevent* bev, short events, void* ctx);
            void accept_error_cb(struct evconnlistener* listener,
                                        void *ctx);
        private:
            int port_;
            HttpRequestParser requestParser_;
        };
    }
}

#endif //HTTPSERVER_SERVER_H
