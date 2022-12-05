/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:23:10 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/05 23:45:04 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Config.hpp"

Config::Config(const char *fileName)
{
	int	fd = 0;
	char buf[BUFFER_SIZE] = {0};
	std::string words[11] = {"listen", "location", "server_name", "body_size",
							 "error_page", "root", "index", "autoindex",
							 "method", "exec_cgi", "extension_cgi"};
	for (int i = 0; i < 11; i++)
		_keyWords[i] = words[i];
	_serverTable.reserve(2);
	if ((fd = open(fileName, O_RDONLY)) == -1)
		throw std::runtime_error("Config file not found");
	while (read(fd, buf, BUFFER_SIZE))
		_contentString += buf;
	close(fd);
	std::size_t start = 0;
	std::size_t end = 0;
	while (start = _contentString.find('#') != std::string::npos)
	{
		end = _contentString.find('\n', start);
		_contentString.erase(start, end - start);
	}
}

Config::~Config() {}

std::vector<Server> *Config::getConfig()
{
	return &_serverTable;
}

void	Config::parse()
{
	std::pair<std::string, bool> pair;
	bool inServer = false, inLocation = false;
	int pos = 0;
	int servCount = 0;
	if (std::count(_contentString.begin(), _contentString.end(), '{') - 
	     std::count(_contentString.begin(), _contentString.end(), '}') != 0)
		 	throw std::runtime_error("Config file error");
	while(_contentString[pos])
	{
		if(_contentString[pos] == '}')
			pos++;
		while (isspace(_contentString[pos]))
			pos++;
		if (!(_contentString[pos]))
			break;
		if (_contentString.substr(pos, 6) == "server")
			pos += 6;
		else
			throw std::runtime_error("No \"server\" in config file");
		
		while (isspace(_contentString[pos]))
			pos++;
		
		if (_contentString[pos] == '{')
		{
			pos++;
			inServer = true;
		}
		else
			throw std::runtime_error("Config file error");
		
		while (isspace(_contentString[pos]))
			pos++;
		ret = isKeyWords(_contentString.substr(pos), _keyWords, 11);
	}
}
