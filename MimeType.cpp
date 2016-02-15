//
// Created by Саид on 14.02.16.
//

#include "MimeType.h"

namespace http {
    namespace server {
        namespace mime_types {
            struct MimeTypeMapping {
                const char *extension;
                const char *mimeType;
            } mappings[] = {
                    {"gif", "image/gif"},
                    {"htm", "text/html"},
                    {"html", "text/html"},
                    {"jpg", "image/jpeg"},
                    {"png", "image/png"}
            };

            std::string extensionToType(const std::string &extension)
            {
                for (MimeTypeMapping m: mappings) {
                    if (m.extension == extension) {
                        return m.mimeType;
                    }
                }

                return "text/plain";
            }
        }
    }
}
