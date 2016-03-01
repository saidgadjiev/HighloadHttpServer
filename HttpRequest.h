//
// Created by Саид on 15.02.16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include "Header.h"
#include "QueryParameter.h"
#include <vector>
#include <cstring>

namespace http {
    namespace server {
        class HttpRequest {
        public:
            HttpRequest() {}
            ~HttpRequest() {}

            std::string& getMethod();
            std::string& getUri();
            std::vector<Header>& getHeaders();
            std::vector<QueryParameter>& getQueryParameters();
            int getHttpVersionMajor() const;
            int getHttpVersionMinor() const;
            void setMethod(std::string method);
            void setUri(std::string uri);
            void setHeader(Header header, int i);
            void setQueryParameter(QueryParameter parameter, int i);
            void addHeader(Header header);
            void addQueryParameter(QueryParameter parameter);
            void setHttpVersionMajor(int httpVersionMajor);
            void setHttpVersionMinor(int httpVersionMinor);
            void pushBackMethod(char ch);
        private:
            std::string method_;
            std::string uri_;
            std::vector<Header> headers_;
            std::vector<QueryParameter> queryParameters_;
            int httpVersionMajor_;
            int httpVersionMinor_;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
