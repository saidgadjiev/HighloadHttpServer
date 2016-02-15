//
// Created by Саид on 15.02.16.
//

#include "HttpResponse.h"

namespace http {
    namespace server {
        namespace statusStrings {
            const std::string OK =
                    "HTTP/1.0 200 OK\r\n";
            const std::string CREATED =
                    "HTTP/1.0 201 Created\r\n";
            const std::string ACCEPTED =
                    "HTTP/1.0 202 Accepted\r\n";
            const std::string NO_CONTENT =
                    "HTTP/1.0 204 No Content\r\n";
            const std::string MULTIPLE_CHOICES =
                    "HTTP/1.0 300 Multiple Choices\r\n";
            const std::string MOVED_PERMANENTLY =
                    "HTTP/1.0 301 Moved Permanently\r\n";
            const std::string MOVED_TEMPORARILY =
                    "HTTP/1.0 302 Moved Temporarily\r\n";
            const std::string NOT_MODIFIED =
                    "HTTP/1.0 304 Not Modified\r\n";
            const std::string BAD_REQUEST =
                    "HTTP/1.0 400 Bad Request\r\n";
            const std::string UNAUTHORIZED =
                    "HTTP/1.0 401 Unauthorized\r\n";
            const std::string FORBIDDEN =
                    "HTTP/1.0 403 Forbidden\r\n";
            const std::string NOT_FOUND =
                    "HTTP/1.0 404 Not Found\r\n";
            const std::string INTERNAL_SERVER_ERROR =
                    "HTTP/1.0 500 Internal Server Error\r\n";
            const std::string NOT_IMPLEMENTED =
                    "HTTP/1.0 501 Not Implemented\r\n";
            const std::string BAD_GATEWAY =
                    "HTTP/1.0 502 Bad Gateway\r\n";
            const std::string SERVICE_UNAVAILABLE =
                    "HTTP/1.0 503 Service Unavailable\r\n";
        }

        namespace stock_replies {
            const char OK[] = "";
            const char CREATED[] =
                    "<html>"
                            "<head><title>Created</title></head>"
                            "<body><h1>201 Created</h1></body>"
                            "</html>";
            const char ACCEPTED[] =
                    "<html>"
                            "<head><title>Accepted</title></head>"
                            "<body><h1>202 Accepted</h1></body>"
                            "</html>";
            const char NO_CONTENT[] =
                    "<html>"
                            "<head><title>No Content</title></head>"
                            "<body><h1>204 Content</h1></body>"
                            "</html>";
            const char MULTIPLE_CHOICES[] =
                    "<html>"
                            "<head><title>Multiple Choices</title></head>"
                            "<body><h1>300 Multiple Choices</h1></body>"
                            "</html>";
            const char MOVED_PERMANENTLY[] =
                    "<html>"
                            "<head><title>Moved Permanently</title></head>"
                            "<body><h1>301 Moved Permanently</h1></body>"
                            "</html>";
            const char MOVED_TEMPORARILY[] =
                    "<html>"
                            "<head><title>Moved Temporarily</title></head>"
                            "<body><h1>302 Moved Temporarily</h1></body>"
                            "</html>";
            const char NOT_MODIFIED[] =
                    "<html>"
                            "<head><title>Not Modified</title></head>"
                            "<body><h1>304 Not Modified</h1></body>"
                            "</html>";
            const char BAD_REQUEST[] =
                    "<html>"
                            "<head><title>Bad Request</title></head>"
                            "<body><h1>400 Bad Request</h1></body>"
                            "</html>";
            const char UNAUTHORIZED[] =
                    "<html>"
                            "<head><title>Unauthorized</title></head>"
                            "<body><h1>401 Unauthorized</h1></body>"
                            "</html>";
            const char FORBIDDEN[] =
                    "<html>"
                            "<head><title>Forbidden</title></head>"
                            "<body><h1>403 Forbidden</h1></body>"
                            "</html>";
            const char NOT_FOUND[] =
                    "<html>"
                            "<head><title>Not Found</title></head>"
                            "<body><h1>404 Not Found</h1></body>"
                            "</html>";
            const char INTERNAL_SERVER_ERROR[] =
                    "<html>"
                            "<head><title>Internal Server Error</title></head>"
                            "<body><h1>500 Internal Server Error</h1></body>"
                            "</html>";
            const char NOT_IMPLEMENTED[] =
                    "<html>"
                            "<head><title>Not Implemented</title></head>"
                            "<body><h1>501 Not Implemented</h1></body>"
                            "</html>";
            const char BAD_GATEWAY[] =
                    "<html>"
                            "<head><title>Bad Gateway</title></head>"
                            "<body><h1>502 Bad Gateway</h1></body>"
                            "</html>";
            const char SERVICE_UNAVAILABLE[] =
                    "<html>"
                            "<head><title>Service Unavailable</title></head>"
                            "<body><h1>503 Service Unavailable</h1></body>"
                            "</html>";

            std::string toString(HttpResponse::StatusType status) {
                switch (status) {
                    case HttpResponse::OK:
                        return OK;
                    case HttpResponse::CREATED:
                        return CREATED;
                    case HttpResponse::ACCEPTED:
                        return ACCEPTED;
                    case HttpResponse::NO_CONTENT:
                        return NO_CONTENT;
                    case HttpResponse::MULTIPLE_CHOICES:
                        return MULTIPLE_CHOICES;
                    case HttpResponse::MOVED_PERMANENTLY:
                        return MOVED_PERMANENTLY;
                    case HttpResponse::MOVED_TEMPORARILY:
                        return MOVED_TEMPORARILY;
                    case HttpResponse::NOT_MODIFIED:
                        return NOT_MODIFIED;
                    case HttpResponse::BAD_REQUEST:
                        return BAD_REQUEST;
                    case HttpResponse::UNAUTHORIZED:
                        return UNAUTHORIZED;
                    case HttpResponse::FORBIDDEN:
                        return FORBIDDEN;
                    case HttpResponse::NOT_FOUND:
                        return NOT_FOUND;
                    case HttpResponse::INTERNAL_SERVER_ERROR:
                        return INTERNAL_SERVER_ERROR;
                    case HttpResponse::NOT_IMPLEMENTED:
                        return NOT_IMPLEMENTED;
                    case HttpResponse::BAD_GATEWAY:
                        return BAD_GATEWAY;
                    case HttpResponse::SERVICE_UNAVAILABLE:
                        return SERVICE_UNAVAILABLE;
                    default:
                        return INTERNAL_SERVER_ERROR;
                }
            }
        }

        HttpResponse::HttpResponse() {
            headers_.resize(2);
        }

        std::vector<Header> HttpResponse::getHeaders() const {
            return headers_;
        }

        std::string HttpResponse::getContent() const {
            return content_;
        }

        StatusType HttpResponse::getStatus() const {
            return status_;
        }

        void HttpResponse::setHeader(Header header, int i) {
            headers_[i] = header;
        }

        void HttpResponse::addHeader(Header header) {
            headers_.push_back(header);
        }

        void HttpResponse::setStatus(StatusType status) {
            status_ = status;
        }

        void HttpResponse::setContent(std::string content) {
            content_ = content;
        }

        HttpResponse HttpResponse::stockReply(StatusType status) {
            HttpResponse resp;
            resp.setStatus(status);
            resp.setContent(stock_replies::toString(status));
            resp.setHeader(Header("Content-Length", std::to_string(resp.getContent().size())), 0);
            resp.setHeader(Header("Content-Type", "text/html"), 1);

            return resp;
        }
    }
}