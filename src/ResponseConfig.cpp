/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/25 17:22:52 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{
	std::string	ret;
	std::vector<Location> locations = server.getLocations();
	std::vector<Location>::iterator it;

	_error_page = server.getParams()["error_page"];
	_path = removeSlashes(ret);
	_method_allowed = server.getParams()["method_allowed"];
	_autoindex = server.getParams()["autoindex"];

	for (it = locations.begin(); it < locations.end(); it++)
	{
		if (it->getPath() == request.getUri())
		{
			std::map <std::string, std::string> locationMap = it->getLocationMap();
			_body_size =  strtoul(locationMap["body_size"].c_str(), 0, 10);
			//если зашли в location, то метод берем отсюда, если нет, останется из конфига сервера
			_method_allowed = locationMap["method_allowed"];
			_exec_cgi = locationMap["exec_cgi"];
			_extension_cgi = makeCgiVector(locationMap["extension_cgi"], ' ');
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

std::vector<std::string> ResponseConfig::makeCgiVector(std::string extensionStr, const char delim)
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


