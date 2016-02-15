//
// Created by Саид on 14.02.16.
//

#ifndef HTTPSERVER_HEADER_H
#define HTTPSERVER_HEADER_H

#include <iostream>
#include <cstring>

namespace http {
    namespace server {
        struct Header {
            Header(std::string name, std::string value)
                : name(name),
                  value(value)
            {}

            std::string name;
            std::string value;
        };
    }
}


#endif //HTTPSERVER_HEADER_H
