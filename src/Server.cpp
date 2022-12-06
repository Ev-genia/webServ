/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:39:55 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/06 15:03:27 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Server.hpp"

Server::Server()
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

std::map<std::string, std::string>	Server::getParams() const
{
	return _params;
}

int	Server::getSocketFd() const
{
	return _socketFd;
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

void	Server::setAddr()
{
	int	port = std::stoi(_params["listen"]);

	_addrIn.sin_family = AF_INET;
	_addrIn.sin_port = htons(port);
	_addrIn.sin_addr.s_addr = htonl(INADDR_ANY);
}
