//
// Created by Саид on 20.03.16.
//

#ifndef HTTPSERVER_CONFIGURATION_H
#define HTTPSERVER_CONFIGURATION_H

class Configuration {
public:
	static const int PORT = 8000;
	static const int nCPU = 1;
	static char *ROOT_DIR;
};

char *Configuration::ROOT_DIR = (char *) ".";

#endif //HTTPSERVER_CONFIGURATION_H
