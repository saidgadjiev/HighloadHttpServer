//
// Created by Саид on 01.03.16.
//

#ifndef HTTPSERVER_QUERYPARAMETER_H
#define HTTPSERVER_QUERYPARAMETER_H

#include <string>

namespace http {
	namespace server {
		struct PairNameValue {
			PairNameValue() {}
			PairNameValue(std::string name, std::string value)
					: name(name),
					  value(value)
			{}

			std::string name;
			std::string value;
		};
	}
}


#endif //HTTPSERVER_QUERYPARAMETER_H
