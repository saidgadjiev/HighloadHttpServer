//
// Created by Саид on 11.03.16.
//

#ifndef HTTPSERVER_CLIENT_H
#define HTTPSERVER_CLIENT_H


#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>
#include <stdlib.h>

class Client
{
public:
	Client() {};
	~Client() {
		if(output_buffer != NULL) {
			evbuffer_free(output_buffer);
		}
	};
	void setEvBase(event_base *evbase) { this->evbase = evbase; }
	void setBufEv(bufferevent *buf_ev) { this->buf_ev = buf_ev; }
	void setOutputBuffer(evbuffer *output_buffer) { this->output_buffer = output_buffer; }
	void setFd(int fd) { this->fd = fd; }
	event_base* getEvBase() { return evbase; }
	bufferevent* getBufEv() { return buf_ev; }
	evbuffer* getOutputBuffer() { return output_buffer; }
	int getFd() { return fd; }

private:
	int fd;
	struct event_base *evbase;
	struct bufferevent *buf_ev;
	struct evbuffer *output_buffer;
};


#endif //HTTPSERVER_CLIENT_H
