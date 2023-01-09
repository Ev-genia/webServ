/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/09 14:46:38 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{
	std::string	ret;

	_path = removeSlashes(ret);
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
