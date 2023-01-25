/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/25 14:07:25 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{
	std::string	ret;
	std::vector<Location> locations = server.getLocations();
	std::vector<Location>::iterator it;
	// for (it = locations.begin(); it < locations.end(); it++)
	// {
	// 	if (it->getPath() == request.getUri())
	// 	{
	// 		_body_size = it->getLocationMap()["body_size"];
	// 	}
	// }
	
	//this->body_size = server.getLocations()//в каком Location сервера взять body_size???
	_error_page = server.getParams()["error_page"];
	_path = removeSlashes(ret);
	_method_allowed = server.getParams()["method_allowed"];
	_autoindex = server.getParams()["autoindex"];



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
