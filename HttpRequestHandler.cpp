//
// Created by Саид on 24.02.16.
//

#include "HttpRequestHandler.h"

namespace http {
	namespace server {
		HttpRequestHandler::HttpRequestHandler(std::string docRoot)
			: docRoot_(docRoot)
		{ }

		void http::server::HttpRequestHandler::handleRequest(HttpRequest &request,
															 HttpResponse &response) {
			std::string resoursePath = request.getUri();

			if (resoursePath[resoursePath.size() - 1] == '/') {
				resoursePath += "index.html";
			}

			size_t lastSlashPos = resoursePath.find_last_of("/");
			size_t lastDotIndex = resoursePath.find_last_of(".");

			std::string extension = resoursePath.substr(lastDotIndex + 1);

			std::string fullPath = docRoot_ + resoursePath;
			bool fileFound = true;
			bool permDenied = true;
			if (access(fullPath.c_str(), 0) == -1) {
				fileFound = false;
			}
			if (fileFound && (access(fullPath.c_str(), 3) == -1)) {
				permDenied = false;
			}
			if (!fileFound) {
				response = HttpResponse::stockReply(HttpResponse::NOT_FOUND);

				return;
			}
			if (fileFound && !permDenied) {
				response = HttpResponse::stockReply(HttpResponse::FORBIDDEN);

				return;
			}
			std::ifstream fin(fullPath, std::ios_base::in | std::ios_base::binary);

			if (!fin.is_open()) {
				std::cerr << "Файл не может быть открыт или создан" << std::endl;
			}
			char buff[512];

			while (fin.read(buff, sizeof(buff)).gcount() > 0) {
				response.contentAppend(buff, (unsigned long) fin.gcount());
			}

			response.setStatus(HttpResponse::OK);
			response.setHeader(Header("Content-Length", std::to_string(response.getContent().size())), 0);
			response.setHeader(Header("Content-Type", mime_types::extensionToType(extension)), 1);
			response.setHeader(Header("Connection", "close"), 2);
		}
	}
}

