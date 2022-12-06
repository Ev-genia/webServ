/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:24:49 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/06 11:34:40 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Handler.hpp"

Handler::Handler(std::vector<Server> * enterServers): _servers(enterServers)
{
	// _servers = enterServers;
}

Handler::~Handler()
{
}

void	Handler::initFds()
{
	FD_ZERO(&_fdReadSave);
	// FD_ZERO(&_fdWriteSave);
	// FD_ZERO(&_fdRead);
	// FD_ZERO(&_fdWrite);
	_maxFd = 0;
	for (int i = 0; i < _servers->size(); i++)
	{
		(*_servers)[i].initSocket();
		FD_SET((*_servers)[i].getSocketFd(), &_fdReadSave);
		if ((*_servers)[i].getSocketFd() > _maxFd)
			_maxFd = (*_servers)[i].getSocketFd();
	}
	if (_maxFd == 0)
		exitError("Could not init Fds in Handler");
}

void	Handler::serverRun()
{
	while (true)
	{
		fd_set			fdRead;
		fd_set			fdWrite;
		// struct timeval	timeout;
		int				ret;

		ret = 0;
		while (ret == 0)
		{
			// timeout.tv_sec = 1;
			// timeout.tv_usec = 0;
			memcpy(&fdRead, &_fdReadSave, sizeof(_fdReadSave));
			FD_ZERO(&fdWrite);
			for (std::vector<int>::iterator it = _fds.begin(); it != _fds.end(); it++)
			{
				FD_SET(*it, &fdWrite);
			}
			ret = select(_maxFd + 1, &fdRead, &fdWrite, 0, 0);
		}
		if (ret == -1)
			exitError("Select");
		for (int i = 0; i < _servers->size(); i++)
		{

		}
	}
}
