//
// Created by Саид on 20.02.16.
//

#include "HttpRequestParser.h"

namespace http {
	namespace server {
		HttpRequestParser::HttpRequestParser()
				: state_(mmethod_start)
		{}

		HttpRequestParser::~HttpRequestParser() { }

		void HttpRequestParser::reset() {
			state_ = mmethod_start;
		}

		HttpRequestParser::ParseResult HttpRequestParser::parse(HttpRequest &request, char *buffer, int length) {
			int i = 0;

			while (i < length) {
				ParseResult result = consume(request, buffer[i++]);
			}
		}

		HttpRequestParser::ParseResult HttpRequestParser::consume(HttpRequest &request, char input) {
			switch (state_) {
				case mmethod_start:

					;
				case method:
					;
				case url:;
			}
		}
	}
}