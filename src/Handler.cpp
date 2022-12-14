/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:24:49 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/14 11:27:34 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Handler.hpp"

Handler::Handler(std::vector<Server> * enterServers): _servers(enterServers)
{
}

Handler::~Handler()
{
}

void	Handler::initFds()
{
	FD_ZERO(&_fdSet);
	_maxFd = 0;
	for (std::size_t i = 0; i < _servers->size(); i++)
	{
		(*_servers)[i].initSocket();
		FD_SET((*_servers)[i].getSocketFd(), &_fdSet);
		if ((*_servers)[i].getSocketFd() > _maxFd)
			_maxFd = (*_servers)[i].getSocketFd();
	}
	if (_maxFd == 0)
		exitError("Could not init Fds in Handler");
}

void	Handler::processChunk(Client *client)
{
	std::string	head;
	std::string	chunks;
	std::string	subChunk;
	std::string	body;
	int			chunkSize;
	size_t		i;

	head = client->request.substr(0, client->request.find("\r\n\r\n"));
	chunks = client->request.substr(client->request.find("\r\n\r\n") + 4, client->request.size() - 1);
	subChunk = chunks.substr(0, 100);
	body = "";
	chunkSize = strtol(subChunk.c_str(), NULL, 10);
	i = 0;
	while (chunkSize)
	{
		i = chunks.find("\r\n", i) + 2;
		body += chunks.substr(i, chunkSize);
		i += chunkSize + 2;
		subChunk = chunks.substr(i, 100);
		chunkSize = strtol(subChunk.c_str(), NULL, 16);
	}
	client->request = head + "\r\n\r\n" + body + "\r\n\r\n";
}

void	Handler::process(Client *client)
{
	if (client->request.find("Transfer-Encoding: chunked") != std::string::npos &&
		client->request.find("Transfer-Encoding: chunked") < client->request.find("\r\n\r\n"))
		processChunk(client);
	else if (client->request != "")
	{
		Request	request(client->request);

		if (request.getRet() != 200)
			request.setMethod("GET");
	}
}

void	Handler::serverRun()
{
	fd_set			fdRead;
	fd_set			fdWrite;
	int				ret;
	int				fdClient;

	while (true)
	{
		// fd_set			fdRead;
		// fd_set			fdWrite;
		// int				ret;
		// int				fdClient;
		// struct timeval	timeout;

		// bzero(&fdRead, sizeof(_fdSet));
		FD_ZERO(&fdRead);
		// bzero(&fdWrite, sizeof(_fdSet));
		FD_ZERO(&fdWrite);
		memcpy(&fdRead, &_fdSet, sizeof(_fdSet));
		memcpy(&fdWrite, &_fdSet, sizeof(_fdSet));
		ret = select(_maxFd + 1, &fdRead, &fdWrite, 0, 0);
		if (ret == -1)
			exitError("Select");
		//проход по серверам
		for (std::size_t i = 0; i < _servers->size(); i++)
		{
			int	serverFd = (*_servers)[i].getSocketFd();

			if (FD_ISSET(serverFd, &fdRead))
			{
				Client *client = new Client(serverFd);
				client->acceptClient();
				FD_SET(client->getFd(), &_fdSet);
				_clients.push_back(client);
				if (client->getFd() > _maxFd)
					_maxFd = client->getFd();
			}
		}
		//проход по читающим fd
		for (std::vector<Client *>::iterator it = _clients.begin(); /*ret && */it != _clients.end(); it++)
		{
			// int		fdClient = it->getFd();
			char	buffer[RECV_SIZE] = {0};
			// int		ret;

			fdClient = (*it)->getFd();
			if (FD_ISSET(fdClient, &fdRead))
			{
				ret = recv(fdClient, buffer, RECV_SIZE - 1, 0);
				if (ret > 0)
				{
					buffer[ret] = 0;
					(*it)->request += buffer;
				}
//where is a process chank?!
				else if (ret == 0)
				{
					process(*it);
					// _clients.push_back(it);
				}
				else if (ret == -1)
				{
					FD_CLR(fdClient, &_fdSet);
					FD_CLR(fdClient, &fdRead);
					//? delete *it;
					_clients.erase(it);
					it = _clients.begin();//?
				}
				// ret = 0;
				break;
			}
		}
		//проход по пишущим fd
		for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			fdClient = (*it)->getFd();

			if (FD_ISSET(fdClient, &fdWrite))
			{
				ret = send(fdClient, (*it)->getResponse().c_str(), (*it)->getResponse().size(), 0);
				if (ret == -1)
				{
					close(fdClient);
					FD_CLR(fdClient, &_fdSet);
					// client.erase(it);
					_clients.erase(it);
					break;
				}
			}
		}
		//check timeout
	}
}
