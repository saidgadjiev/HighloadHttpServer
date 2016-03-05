//
// Created by Саид on 14.02.16.
//

#include <event2/http.h>
#include "Server.h"
#include "HttpRequestHandler.h"
#include "HttpRequestParser.h"

INITIALIZE_EASYLOGGINGPP

namespace http {
    namespace server {
        Server::Server(int port)
                : port_(port) {
            el::Loggers::reconfigureAllLoggers(el::ConfigurationType::Format,
                                               "%level %datetime{%H:%m:%s} (%func): %msg");
        }

        void Server::read_cb(struct bufferevent *bev, void *ctx) {
            size_t length = evbuffer_get_length(bufferevent_get_input(bev));
            char *data = new char[length];

            evbuffer_remove(bufferevent_get_input(bev), data, length);
            HttpRequestParser requestParser;
            HttpRequest request;
            HttpResponse response;

            requestParser.reset();
            requestParser.parse(request, data, length);
            HttpRequestHandler requestHandler(".");
            requestHandler.handleRequest(&request, &response);
            evbuffer_add(bufferevent_get_output(bev), response.toString().c_str(), response.toString().length());

            delete[] data;
        }

        void Server::write_cb(struct bufferevent *bev, void *ctx) {
            bufferevent_free(bev);
        }

        void Server::event_cb(struct bufferevent *bev, short events, void *ctx) {
            if (events & BEV_EVENT_ERROR) {
                bufferevent_free(bev);
            }

            if (events & BEV_EVENT_EOF) {
                bufferevent_free(bev);
            }

        }

        void Server::accept_error_cb(struct evconnlistener *listener, void *ctx) {
            struct event_base *base = evconnlistener_get_base(listener);
            int err = EVUTIL_SOCKET_ERROR();

            LOG(ERROR) << "Error: " << err << "=" << evutil_socket_error_to_string(err);
            event_base_loopexit(base, NULL);
        }

        static void SIGINTHandler(evutil_socket_t sig, short events, void *user_data) {
            struct event_base *base = (struct event_base*)user_data;
            struct timeval delay = {1, 0};

            LOG(INFO) << "Server shutdown";

            event_base_loopexit(base, &delay);
        }

        void Server::accept_conn_cb(struct evconnlistener *listener,
                                    evutil_socket_t fd,
                                    struct sockaddr *address,
                                    int socklen,
                                    void *ctx) {
            struct event_base *base = evconnlistener_get_base(listener);
            struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);

            bufferevent_setcb(bev, Server::read_cb, Server::write_cb, Server::event_cb, NULL);
            bufferevent_enable(bev, EV_READ);
        }

        void Server::start() {
            struct event_base *eventBase = event_base_new();
            struct sockaddr_in sin;

            sin.sin_family = AF_INET;
            sin.sin_port = htons(port_);
            sin.sin_addr.s_addr = INADDR_ANY;

            struct evconnlistener *listener = evconnlistener_new_bind(eventBase,
                                                                      accept_conn_cb,
                                                                      NULL,
                                                                      LEV_OPT_CLOSE_ON_FREE | LEV_OPT_REUSEABLE,
                                                                      -1,
                                                                      (struct sockaddr *) &sin, sizeof(sin));
            if (!listener) {
                LOG(ERROR) << "Couldn't create listener";
            }
            evconnlistener_set_error_cb(listener, Server::accept_error_cb);
            struct event *signal_event = evsignal_new(eventBase, SIGINT, SIGINTHandler, (void *) eventBase);
            if (!signal_event || event_add(signal_event, NULL) < 0) {
                LOG(INFO) << "Could not create/add a signal event!";
            }
            LOG(INFO) << "Server start";
            event_base_dispatch(eventBase);
        }
    }
}