//
// Created by Саид on 15.02.16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include "Header.h"
#include <vector>
#include <cstring>

namespace http {
    namespace server {

        class HttpRequest {
        public:
            std::string method;
            std::string url;
            std::vector<Header> headers;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
