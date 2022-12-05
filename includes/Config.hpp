#ifndef CONFIG_HPP
# define IFNDEF_HPP
# include <iostream>
# include <vector>
# include "Server.hpp"

class Config
{
private:
	std::string _keyWords[11];
	std::string	_contentString;
	std::vector<Server> _serverTable;
public:
	Config(const char *fileName);
	~Config();
};

#endif