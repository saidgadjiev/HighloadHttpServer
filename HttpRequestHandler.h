//
// Created by Саид on 24.02.16.
//

#ifndef HTTPSERVER_HTTPREQUESTHANDLER_H
#define HTTPSERVER_HTTPREQUESTHANDLER_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include "MimeType.h"
#include <fstream>
#include <easylogging++.h>

namespace http {
	namespace server {
		class HttpRequestHandler {
		public:
			HttpRequestHandler(std::string docRoot);
			void handleRequest(HttpRequest &request, HttpResponse &response);
		private:
			std::string docRoot_;
		};
	}
}

#endif //HTTPSERVER_HTTPREQUESTHANDLER_H
