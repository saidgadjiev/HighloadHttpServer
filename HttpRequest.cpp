//
// Created by Саид on 15.02.16.
//

#include "HttpRequest.h"

namespace http {
    namespace server {
        std::string& HttpRequest::getMethod() {
            return method_;
        }

        std::string& HttpRequest::getUri() {
            return uri_;
        }

        std::vector<Header>& HttpRequest::getHeaders(){
            return headers_;
        }

        void HttpRequest::setMethod(std::string method) {
            method_ = method;
        }

        void HttpRequest::setUri(std::string uri) {
            uri_ = uri;
        }

        void HttpRequest::setHeader(Header header, int i) {
            headers_[i] = header;
        }

        void HttpRequest::addHeader(Header header) {
            headers_.push_back(header);
        }

        int HttpRequest::getHttpVersionMajor() const {
            return httpVersionMajor_;
        }

        int HttpRequest::getHttpVersionMinor() const {
            return httpVersionMinor_;
        }

        void HttpRequest::setHttpVersionMajor(int httpVersionMajor) {
            httpVersionMajor_ = httpVersionMajor;
        }

        void HttpRequest::setHttpVersionMinor(int httpVersionMinor) {
            httpVersionMinor_ = httpVersionMinor;
        }

        void HttpRequest::pushBackMethod(char ch) {
            method_.push_back(ch);
        }

        std::vector<QueryParameter> &HttpRequest::getQueryParameters() {
            return queryParameters_;
        }

        void HttpRequest::setQueryParameter(QueryParameter parameter, int i) {
            queryParameters_[i] = parameter;
        }

        void HttpRequest::addQueryParameter(QueryParameter parameter) {
            queryParameters_.push_back(parameter);
        }
    }
}