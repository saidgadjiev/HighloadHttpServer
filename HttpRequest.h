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
            HttpRequest() {}
            ~HttpRequest() {}

            std::string getMethod() const;
            std::string getUrl() const;
            std::vector<Header> getHeaders() const;
            void setMethod(std::string method);
            void setUrl(std::string url);
            void setHeader(Header header, int i);
            void addHeader(Header header);
        private:
            std::string method_;
            std::string url_;
            std::vector<Header> headers_;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
