/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:39:55 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/20 17:12:01 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Server.hpp"

Server::Server(): _locations()
{
	_socketFd = -1;
	_autoindex = false;
}

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
	struct sockaddr *addr = reinterpret_cast<struct sockaddr *>(&_addrIn);
	_socketFd = socket(_addrIn.sin_family, SOCK_STREAM, 0);
	if (_socketFd == -1)
		exitError("Socket");
	// setsockopt(_socketFd, SOL_SOCKET, SO_REUSEADDR, &_reuse, sizeof(int));
	if (bind(_socketFd, addr, sizeof(*addr)) == -1)
		exitError("Bind");
	if (listen(_socketFd, 32) == -1)
		exitError("Listem");
}

void	Server::setAutoindex(bool index)
{
	this->_autoindex = index;
}

void	Server::setAddr()//TODO:Переделать _params на вектор listens
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


