/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:49:54 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/07 16:57:24 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Client.hpp"

Client::Client(int enterServerFd): _serverFd(enterServerFd), _fd(-1), _response("")
{
	memset(&_clientAddrIn, 0, sizeof(_clientAddrIn));
	// memset(&_timeout, 0, sizeof(_timeout));
	// gettimeofday(&_timeout, 0);
	this->request = "";
}

Client::~Client()
{
}

int	Client::getFd() const
{
	return (_fd);
}

void	Client::acceptClient()
{
	int	addrLen;

	struct sockaddr *clientAddr = reinterpret_cast<struct sockaddr *>(&_clientAddrIn);
	addrLen = sizeof(*clientAddr);
	socklen_t	*addrLenSockLen = reinterpret_cast<socklen_t *>(addrLen);
	_fd = accept(_serverFd, clientAddr, addrLenSockLen);
	if (_fd < 0)
		exitError("Accept");
}
