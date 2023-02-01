/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:23:39 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{
	std::string	ret;
	std::vector<Location> locations = server.getLocations();
	std::vector<Location>::iterator it;
	std::map<std::string, std::string> serverParams = server.getParams();
	_error_page = serverParams["error_page"];
//_path = removeSlashes(ret);
	_root = serverParams["root"];
	_method_allowed = makeSet(makeVector(serverParams["method_allowed"], ' '));

	if (serverParams.find("autoindex") != serverParams.end() && serverParams["autoindex"] == "on")
		_autoindex = true;
	else
		_autoindex = false;

	for (it = locations.begin(); it < locations.end(); it++)
	{
		if (request.getUri().find(it->getPath()) != std::string::npos)//есть ли в uri эта часть it->getPath, а не полносе совпадение
		{
			std::map <std::string, std::string> locationMap = it->getLocationMap();
			_body_size =  strtoul(locationMap["body_size"].c_str(), 0, 10);
			//если зашли в location, то метод берем отсюда, если нет, останется из конфига сервера
			_method_allowed = makeSet(makeVector(locationMap["method_allowed"], ' '));
			_exec_cgi = locationMap["exec_cgi"];
			_extension_cgi = makeVector(locationMap["extension_cgi"], ' ');
			_root = locationMap["root"];
		}
	}
}

ResponseConfig::~ResponseConfig()
{}

Server	&ResponseConfig::getServer() const
{
	return (_server);
}

const std::string	&ResponseConfig::getPath() const
{
	return (_path);
}

std::string	ResponseConfig::removeSlashes(const std::string &str)
{
	std::string	ret;
	bool		lastSlash = false;

	for (std::string::size_type i = 0; i < str.length(); i++)//std::string::size_type Это тип, который достаточно велик, чтобы представить размер строки, независимо от того, насколько велика эта строка.
	{
		if (str[i] == '/')
		{
			if (!lastSlash)
				ret.push_back(str[i]);
			lastSlash = true;
		}
		else
		{
			lastSlash = false;
			ret.push_back(str[i]);
		}
	}
	return (ret);
}

std::vector<std::string> ResponseConfig::makeVector(std::string extensionStr, const char delim)
{
	std::vector<std::string>	result;
	size_t start;
    size_t end = 0;
 
    while ((start = extensionStr.find_first_not_of(delim, end)) != std::string::npos)
    {
        end = extensionStr.find(delim, start);
        result.push_back(extensionStr.substr(start, end - start));
    }
	return result;
}

std::set<std::string>		ResponseConfig::makeSet(std::vector<std::string> vect)
{
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
		this->_method_allowed.insert(*i);
}

bool const	&ResponseConfig::getAutoIndex() const
{
	return _autoindex;
}

const t_listen	&ResponseConfig::getHostPort() const {
	return this->_hostPort;
}

 std::set<std::string>		ResponseConfig::getAllowedMethods() const {
	return _method_allowed;
}

unsigned long		ResponseConfig::getBodySize() const
{
	return _body_size;
}
