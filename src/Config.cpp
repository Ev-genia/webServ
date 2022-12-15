/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:23:10 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/14 17:32:36 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Config.hpp"

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
	while ((start = _contentString.find('#')) != std::string::npos)
	{
		end = _contentString.find('\n', start);
		_contentString.erase(start, end - start);
	}
}

Config::~Config() {}

std::pair<std::string, bool> Config::isKeyWord(std::string src, std::string keyWords[], int num)
{
	for (int i = 0; i < num; i++)
	{
		if ((src.compare(0, keyWords[i].size(), keyWords[i])) == 0)
			return std::make_pair(keyWords[i], true);
	}
	return std::make_pair("", false);	
}

void	Config::trimConfigStr(std::string &str)
{
	str.erase(0, str.find_first_not_of(" "));
	while (str.back() == ' ')	
		str.erase(str.back());
}

std::pair<std::string, std::string> Config::splitConfigParam(std::string src)
{
	int space = src.find(" ");
	std::string first = src.substr(0, space);
	while (isspace(src[space]))
		space++;
	int lenSecond = space;
	while (src[lenSecond] != ';' && src[lenSecond] != '\n')
		lenSecond++;
	std::string second = src.substr(space, lenSecond - space);
	this->trimConfigStr(first);
	this->trimConfigStr(second);
	return (std::make_pair(first, second));
}

std::vector<Server> *Config::getConfig()
{
	return &_serverTable;
}

std::string	Config::extractPathFromStrConfig(std::string src, int pos)
{
	int lenStr = pos;
	while(isspace(src[lenStr]) == 0 && src[lenStr] != '{')
		lenStr++;
	return (src.substr(pos, lenStr - pos));
}

void		Config::parseServerConfig(bool &inServer, bool &inLocation, int &pos, int &servCount)
{
	std::pair<std::string, bool> wordInConfig;
	Server s;

	wordInConfig = this->isKeyWord(_contentString.substr(pos), _keyWords, 11);
	_serverTable.push_back(s);
	while(wordInConfig.second == true && wordInConfig.first != "server" &&
		inLocation == false && inServer == true)
	{
		std::pair<std::string, std::string> param = this->splitConfigParam(_contentString.substr(pos));
		_serverTable[servCount].getParams().insert(param);
		while (_contentString[pos] != '\n')
			pos++;
		while (isspace(_contentString[pos]))
			pos++;
		wordInConfig = this->isKeyWord(_contentString.substr(pos), _keyWords, 11);
		if (wordInConfig.first == "location" && inServer == true)	
			this->parseLocationConfig(inLocation, pos, servCount, wordInConfig);
	}
}

void	Config::parseLocationConfig(bool &inLocation, int &pos, int &servCount, std::pair<std::string, bool> &wordInConfig)
{
	std::pair<std::string, std::string> param;

	while (wordInConfig.first == "location")
	{
		inLocation = true;
		pos += 8;
		while (isspace(_contentString[pos]))
			pos++;
		Location loc;
		loc.setPath(this->extractPathFromStrConfig(_contentString, pos));
		pos += loc.getPath().size();
		while (_contentString[pos] == '{' || isspace(_contentString[pos]))
			pos++;
		wordInConfig = this->isKeyWord(_contentString.substr(pos), _keyWords, 11);

		while (wordInConfig.second == true)
		{
			param = this->splitConfigParam(_contentString.substr(pos));
			loc.getLocationStrMap().insert(param);
			while (_contentString[pos] != '\n')
				pos++;
			while (isspace(_contentString[pos]))
				pos++;
			wordInConfig = this->isKeyWord(_contentString.substr(pos), _keyWords, 11);
		}
		_serverTable[servCount].getLocations().push_back(loc);
		while (inLocation && (isspace(_contentString[pos]) || _contentString[pos] == '}'))
		{
			if (_contentString[pos] == '}')
				inLocation = false;
			pos++;
		}
		while (isspace(_contentString[pos]))
			pos++;
		wordInConfig = this->isKeyWord(_contentString.substr(pos), _keyWords, 11);
	}
}

void	Config::parse()
{
std::pair<std::string, bool> wordInConfig;
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
			break ;
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
		this->parseServerConfig(inServer, inLocation, pos, servCount);
 		servCount++;
	}
	this->check();
}
