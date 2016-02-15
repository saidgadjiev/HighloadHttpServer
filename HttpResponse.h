//
// Created by Саид on 15.02.16.
//

#ifndef HTTPSERVER_HTTPRESPONSE_H
#define HTTPSERVER_HTTPRESPONSE_H


#include <vector>
#include <cstring>
#include "Header.h"

namespace http {
    namespace server {
        class HttpResponse {
        public:
            enum StatusType{
                OK = 200,
                CREATED = 201,
                ACCEPTED = 202,
                NO_CONTENT = 204,
                MULTIPLE_CHOICES = 300,
                MOVED_PERMANENTLY = 301,
                MOVED_TEMPORARILY = 302,
                NOT_MODIFIED = 304,
                BAD_REQUEST = 400,
                UNAUTHORIZED = 401,
                FORBIDDEN = 403,
                NOT_FOUND = 404,
                INTERNAL_SERVER_ERROR = 500,
                NOT_IMPLEMENTED = 501,
                BAD_GATEWAY = 502,
                SERVICE_UNAVAILABLE = 503
            } status;

            static HttpResponse stockReply(StatusType status);

            std::vector<Header> headers;
            std::string content;
        };
    }
}

#endif //HTTPSERVER_HTTPRESPONSE_H
