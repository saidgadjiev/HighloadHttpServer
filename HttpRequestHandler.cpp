//
// Created by Саид on 24.02.16.
//

#include "HttpRequestHandler.h"

namespace http {
	namespace server {
		HttpRequestHandler::HttpRequestHandler(std::string docRoot)
			: docRoot_(docRoot)
		{ }

		void http::server::HttpRequestHandler::handleRequest(HttpRequest *request,
															 HttpResponse *response) {
			std::string resoursePath = request->getUri();

			if (!urlDecode(request->getUri(), &resoursePath)) {
				*response = HttpResponse::stockReply(HttpResponse::BAD_REQUEST);

				return;
			}
			if (resoursePath.empty() || resoursePath[0] != '/' || resoursePath.find("..") != std::string::npos) {
				*response = HttpResponse::stockReply(HttpResponse::BAD_REQUEST);

				return;
			}
			if (resoursePath[resoursePath.size() - 1] == '/') {
				resoursePath += "index.html";
			}
			size_t lastSlashPos = resoursePath.find_last_of("/");
			size_t lastDotPos = resoursePath.find_last_of(".");
			std::string extension;

			if (lastDotPos != std::string::npos && lastDotPos > lastSlashPos) {

				extension = resoursePath.substr(lastDotPos + 1);
			}
			std::string fullPath = docRoot_ + resoursePath;

			if (access(fullPath.c_str(), 0) == -1) {
				*response = HttpResponse::stockReply(HttpResponse::NOT_FOUND);

				return;
			}
			if (access(fullPath.c_str(), 3) == -1) {
				*response = HttpResponse::stockReply(HttpResponse::FORBIDDEN);

				return;
			}
			std::ifstream fin(fullPath, std::ios_base::in | std::ios_base::binary);
			char buff[512];

			while (fin.read(buff, sizeof(buff)).gcount() > 0) {
				response->contentAppend(buff, (unsigned long) fin.gcount());
			}

			response->setStatus(HttpResponse::OK);
			response->setHeader(Header("Content-Length", std::to_string(response->getContent().size())), 0);
			response->setHeader(Header("Content-Type", mime_types::extensionToType(extension)), 1);
			response->setHeader(Header("Connection", "close"), 2);
		}

		bool HttpRequestHandler::urlDecode(const std::string &in, std::string *out) {
			out->clear();
			out->reserve(in.size());
			for (size_t i = 0; i < in.size(); ++i) {
				if (in[i] == '%') {
					if (i + 3 <= in.size()) {
						int value = 0;
						std::istringstream is(in.substr(i + 1, 2));

						if (is >> std::hex >> value) {
							*out += static_cast<char>(value);
							i += 2;
						} else {
							return false;
						}
					}
				} else {
					*out += in[i];
				}
			}

			return true;
		}
	}
}

