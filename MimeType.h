//
// Created by Саид on 14.02.16.
//

#ifndef HTTPSERVER_MIMETYPES_H
#define HTTPSERVER_MIMETYPES_H

#include <iostream>
#include <cstring>

namespace http {
    namespace server {
        namespace mime_types {
            std::string extensionToType(const std::string &extension);
        }
    }
}


#endif //HTTPSERVER_MIMETYPES_H
