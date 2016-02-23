//
// Created by Саид on 20.02.16.
//

#ifndef HTTPSERVER_HTTPREQUESTPARSER_H
#define HTTPSERVER_HTTPREQUESTPARSER_H

#include "HttpRequest.h"

namespace http {
	namespace server {
		class HttpRequestParser {
		public:
			HttpRequestParser();
			~HttpRequestParser();

			void reset();

			enum ParseResult {good, bad, indeterminate};

			ParseResult parse(HttpRequest &request, char *buffer, int length);
		private:
			ParseResult consume(HttpRequest &request, char input);
			enum State {
				mmethod_start,
				method,
				url
			} state_;
		};
	}
}



#endif //HTTPSERVER_HTTPREQUESTPARSER_H
