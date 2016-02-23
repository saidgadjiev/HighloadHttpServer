//
// Created by Саид on 15.02.16.
//

#include "HttpRequest.h"

namespace http {
    namespace server {
        std::string& HttpRequest::getMethod() const {
            return method_;
        }

        std::string& HttpRequest::getUrl() const {
            return url_;
        }

        std::vector<Header>& HttpRequest::getHeaders() const {
            return headers_;
        }

        void HttpRequest::setMethod(std::string method) {
            method_ = method;
        }

        void HttpRequest::setUrl(std::string url) {
            url_ = url;
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
    }
}