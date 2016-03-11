//
// Created by Саид on 15.02.16.
//

#ifndef HTTPSERVER_HTTPREQUEST_H
#define HTTPSERVER_HTTPREQUEST_H

#include "PairNameValue.h"
#include "PairNameValue.h"
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
            std::vector<PairNameValue>& getHeaders();
            std::vector<PairNameValue>& getQueryParameters();
            int getHttpVersionMajor() const;
            int getHttpVersionMinor() const;
            void addHeader(PairNameValue header);
            void addQueryParameter(PairNameValue parameter);
            void setHttpVersionMajor(int httpVersionMajor);
            void setHttpVersionMinor(int httpVersionMinor);
            void pushBackMethod(char ch);
            void pushBackUri(char ch);
        private:
            std::string method_;
            std::string uri_;
            std::vector<PairNameValue> headers_;
            std::vector<PairNameValue> queryParameters_;
            int httpVersionMajor_;
            int httpVersionMinor_;
        };
    }
}


#endif //HTTPSERVER_HTTPREQUEST_H
