#include "Config.hpp"

Config::Config(const char *fileName)
{
	std::string words[11] = {"listen", "location", "server_name", "body_size",
							 "error_page", "root", "index", "autoindex",
							 "method", "exec_cgi", "extension_cgi"};
	for (int i = 0; i < 11; i++)
		_keyWords[i] = words[i];
	_serverTable.reserve(2);
}