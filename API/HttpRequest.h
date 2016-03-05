//
// Created by Саид on 15.02.16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include "NameValue.h"
#include "NameValue.h"
#include <vector>
#include <cstring>

namespace http {
    namespace server {
        class HttpRequest {
        public:
            HttpRequest() {}
            ~HttpRequest() {}

            std::string getMethod();
            std::string getUri();
            std::vector<NameValue>& getHeaders();
            std::vector<NameValue>& getQueryParameters();
            int getHttpVersionMajor() const;
            int getHttpVersionMinor() const;
            void addHeader(NameValue header);
            void addQueryParameter(NameValue parameter);
            void setHttpVersionMajor(int httpVersionMajor);
            void setHttpVersionMinor(int httpVersionMinor);
            void pushBackMethod(char ch);
            void pushBackUri(char ch);
        private:
            std::string method_;
            std::string uri_;
            std::vector<NameValue> headers_;
            std::vector<NameValue> queryParameters_;
            int httpVersionMajor_;
            int httpVersionMinor_;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
