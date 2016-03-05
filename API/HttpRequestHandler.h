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
			void handleRequest(HttpRequest *request, HttpResponse *response);
			bool isAllowMethod(std::string method);
			bool isMethodWithContent(std::string method);
			int getFileLength(std::ifstream &fin);
			std::string getFileExtension(std::string path);
		private:
			bool urlDecode(const std::string &in, std::string *out);
			void writeContentToRequest(std::ifstream &fin, HttpResponse *response);
			std::string docRoot_;

		};
	}
}

#endif //HTTPSERVER_HTTPREQUESTHANDLER_H
