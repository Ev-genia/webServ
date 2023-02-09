/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/06 12:30:48 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): /*_hostPort(server.getListen()), */_server(server), _request(request)
{
// t_listen	tmp = server.getListen();
	std::string	ret;
	std::vector<Location> locations = server.getLocations();
	std::vector<Location>::iterator it;
	std::map<std::string, std::string> serverParams = server.getParams();
	initErrorPages();
//_path = removeSlashes(ret);
	_root = serverParams["root"];
	_exec_cgi = "";
	_method_allowed = makeSet(makeVector(serverParams["method_allowed"], ' '));

	if (serverParams.find("autoindex") != serverParams.end() && serverParams["autoindex"] == "on")
		_autoindex = true;
	else
		_autoindex = false;
	_locationPath = "";
	for (it = locations.begin(); it != locations.end(); it++)
	{
		if (_request.getUri().find(it->getPath()) != std::string::npos)//есть ли в uri эта часть it->getPath, а не полное совпадение
		{
// std::cout << "_request.getUri(): " << _request.getUri() << ", it->getPath(): " << it->getPath() << std::endl;
			std::map <std::string, std::string> locationMap = it->getLocationMap();
			_body_size =  strtoul(locationMap["body_size"].c_str(), 0, 10);
			//если зашли в location, то метод берем отсюда, если нет, останется из конфига сервера
			_method_allowed = makeSet(makeVector(locationMap["method_allowed"], ' '));
			_exec_cgi = locationMap["exec_cgi"];
			_extension_cgi = makeVector(locationMap["extension_cgi"], ' ');
			_root = locationMap["root"];
			_locationPath = it->getPath();

			if (*(--_locationPath.end()) == '/')
				_locationPath.resize(_locationPath.size() - 1);

			break;
		}
	}
	std::string temp;
	if (_locationPath[0] != '*' && _locationPath != "")
	{
		if (_request.getUri().find(_root) != std::string::npos)
			temp = _request.getUri();
		else
			temp = _root + _request.getUri().substr(_locationPath.length());
		_contentLocation = removeSlashes(_request.getUri().substr(_locationPath.length()));
	// std::cout << "root: " << _root << ", _request.getUri().substr(_locationPath.length()): " << _request.getUri().substr(_locationPath.length()) << std:: endl;
	}
	else
	{
		if (_request.getUri().find(_root) != std::string::npos)
			temp = _request.getUri();
		else
			temp = _root + _request.getUri();
		_contentLocation = removeSlashes(_request.getUri());
	
	}
	_path = removeSlashes(temp);
std::cout << "ResponseConfig::ResponseConfig| _path: " << _path << std::endl;
	_hostPort = &(server.getListen());
}

ResponseConfig::~ResponseConfig()
{}

void	ResponseConfig::initErrorPages()
{
	_errorPage[204] = "www/errors/204.html";
	_errorPage[400] = "www/errors/400.html";
	_errorPage[403] = "www/errors/403.html";
	_errorPage[404] = "www/errors/404.html";
	_errorPage[405] = "www/errors/405.html";
	_errorPage[406] = "www/errors/406.html";
	_errorPage[409] = "www/errors/409.html";
	_errorPage[413] = "www/errors/413.html";
	_errorPage[415] = "www/errors/415.html";
	_errorPage[500] = "www/errors/500.html";
	_errorPage[501] = "www/errors/501.html";
	_errorPage[505] = "www/errors/505.html";
}

Server	&ResponseConfig::getServer() const
{
	return (_server);
}

const std::string	&ResponseConfig::getLocationPath() const
{
	return (_locationPath);
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

	//if (extensionStr != NULL)
	//{
		while ((start = extensionStr.find_first_not_of(delim, end)) != std::string::npos)
		{
			end = extensionStr.find(delim, start);
			result.push_back(extensionStr.substr(start, end - start));
		}
//	}
	return result;
}

std::set<std::string>		ResponseConfig::makeSet(std::vector<std::string> vect)
{
	for (std::vector<std::string>::iterator i = vect.begin(); i != vect.end(); i++)
		this->_method_allowed.insert(*i);
	return (_method_allowed);
}

bool const	&ResponseConfig::getAutoIndex() const
{
	return _autoindex;
}

struct s_listen	*ResponseConfig::getHostPort()
{
	return (_hostPort);
}

std::set<std::string>		ResponseConfig::getAllowedMethods() const {
	return _method_allowed;
}

std::string&	ResponseConfig::getCgiExec()
{
	return (_exec_cgi);
}


unsigned long		ResponseConfig::getBodySize() const
{
	return _body_size;
}

const std::string		&ResponseConfig::getPath() const
{
	return _path;
}

const std::string		&ResponseConfig::getContentLocation() const
{
	return _contentLocation;
}

const std::map<int, std::string>	&ResponseConfig::getErrorPage() const
{
	return (_errorPage);
}
