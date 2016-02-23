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

            std::string& getMethod();
            std::string& getUrl();
            std::vector<Header>& getHeaders();
            int getHttpVersionMajor() const;
            int getHttpVersionMinor() const;
            void setMethod(std::string method);
            void setUrl(std::string url);
            void setHeader(Header header, int i);
            void addHeader(Header header);
            void setHttpVersionMajor(int httpVersionMajor);
            void setHttpVersionMinor(int httpVersionMinor);
            void pushBackMethod(char ch);
        private:
            std::string method_;
            std::string url_;
            std::vector<Header> headers_;
            int httpVersionMajor_;
            int httpVersionMinor_;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
