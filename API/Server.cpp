//
// Created by Саид on 14.02.16.
//

#include "Server.h"
#include "Configuration.h"

namespace http {
    namespace server {
        char *HttpServer::rootDir_;
        workqueue_t HttpServer::workqueue;

        HttpServer::HttpServer()
        {
            evthread_use_pthreads();
            //TODO: Signal handling
        }

        HttpServer::~HttpServer()
        {
        }

        void HttpServer::startServer(int port, int nCPU, char *rootDir)
        {
            struct sockaddr_in listenAddr;
            struct event_base *base;
            struct evconnlistener *listener;

            rootDir_ = rootDir;
            base = event_base_new();
            if (!base) {
                throw std::runtime_error("Can't create base");
            }
            if (evthread_make_base_notifiable(base) < 0) {
                event_base_free(base);
                throw std::runtime_error("Couldn't make base notifiable!");
            }
            memset(&listenAddr, 0, sizeof(listenAddr));
            listenAddr.sin_family = AF_INET;
            listenAddr.sin_addr.s_addr = htonl(0);
            if(port == 0) {
                port = Configuration::PORT;
            }
            listenAddr.sin_port = htons(port);
            if(nCPU == 0) {
                nCPU = Configuration::nCPU;
            }
            WorkQueue::workqueue_init((workqueue_t *)&workqueue, nCPU);
            listener = evconnlistener_new_bind(base, acceptConnCb, (void *)&workqueue,
                                               LEV_OPT_CLOSE_ON_FREE|LEV_OPT_REUSEABLE|LEV_OPT_THREADSAFE, 20,
                                               (struct sockaddr*)&listenAddr, sizeof(listenAddr));
            if (listener == NULL) {
                event_base_free(base);
                WorkQueue::workqueue_shutdown(&workqueue);
                throw std::runtime_error("Port is busy");
            }
            evconnlistener_set_error_cb(listener, acceptErrorCb);
            event_base_dispatch(base);
            event_base_free(base);
            WorkQueue::workqueue_shutdown(&workqueue);
        }

        void HttpServer::acceptConnCb(evconnlistener *listener, int fd, sockaddr *address, int socklen, void *arg)
        {
            struct event_base *base = evconnlistener_get_base(listener);
            struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE|BEV_OPT_THREADSAFE);

            workqueue_t *workqueue = (workqueue_t *)arg;
            Client* client = new Client();
            client->setBufEv(bev);
            client->setEvBase(base);
            client->setOutputBuffer(evbuffer_new());

            job_t *job = new job_t;
            job->job_function = serverJobFunction;
            job->user_data = client;
            WorkQueue::workqueue_add_job(workqueue, job);
        }

        void HttpServer::acceptErrorCb(evconnlistener *listener, void *ctx)
        {
            struct event_base *base = evconnlistener_get_base(listener);
            int err = EVUTIL_SOCKET_ERROR();
            std::cout << "Got an error on the listener. (" << err << ") " << evutil_socket_error_to_string(err);
            event_base_loopexit(base, NULL);
        }

        void HttpServer::readCb(bufferevent *bev, void *ctx)
        {
            size_t length = evbuffer_get_length(bufferevent_get_input(bev));
            char *data = (char *) malloc(sizeof(char) * length);

            evbuffer_remove(bufferevent_get_input(bev), data, length);
            HttpRequestParser requestParser;
            HttpRequest request;
            HttpResponse response;

            requestParser.reset();
            requestParser.parse(request, data, length);
            HttpRequestHandler requestHandler(rootDir_);
            requestHandler.handleRequest(&request, &response);
            evbuffer_add(bufferevent_get_output(bev), response.toString().c_str(), response.toString().length());

            free(data);
        }

        void HttpServer::eventCb(bufferevent *bev, short events, void *ctx)
        {
            if (events & BEV_EVENT_ERROR)
                std::cout << "bufferevent error!" << std::endl;
            if (events & (BEV_EVENT_EOF | BEV_EVENT_ERROR)) {
                bufferevent_free(bev);
            }
        }

        void HttpServer::writeCb(bufferevent *bev, void *ctx)
        {
            bufferevent_free(bev);
        }

        void HttpServer::serverJobFunction(job *job)
        {
            Client *client = (Client *)job->user_data;
            bufferevent_setcb(client->getBufEv(), readCb, writeCb, eventCb, NULL);
            bufferevent_enable(client->getBufEv(), EV_PERSIST|EV_TIMEOUT|EV_READ);

            delete client;
            delete job;
        }
    }
}