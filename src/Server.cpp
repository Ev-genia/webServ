/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:39:55 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/07 23:23:28 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

// Server::Server(): _locations()
// {
// 	_socketFd = -1;
// 	_autoindex = false;
// }

Server::~Server()
{}

bool	Server::getAutoIndex() const
{
	return _autoindex;
}

std::map<std::string, std::string>	&Server::getParams()
{
	return _params;
}

int	Server::getSocketFd() const
{
	return _socketFd;
}

std::vector<Location> Server::getLocations() const
{
	return this->_locations;
}

t_listen		&Server::getListen()
{
	return _listen;
}


void	Server::initSocket()
{
	setAddr();
	_socketFd = socket(_addrIn.sin_family, SOCK_STREAM, 0);
	if (_socketFd == -1)
		exitError("Socket");
	_reuse = 1;
	setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &_reuse, sizeof(int));
	if (bind(_socketFd, (struct sockaddr *)&_addrIn, sizeof(_addrIn)) == -1)
		exitError("Bind");
	if (listen(_socketFd, 32) == -1)
		exitError("Listen");
}

void	Server::setAutoindex(bool index)
{
	this->_autoindex = index;
}

void	Server::setAddr()
{
	memset((char *)&_addrIn, 0, sizeof(_addrIn));
	_addrIn.sin_family = AF_INET;
	_addrIn.sin_port = htons(_listen.port);
	_addrIn.sin_addr.s_addr = htonl(_listen.host);
}

void	Server::setListen(t_listen value)
{
	this->_listen = value;
}


