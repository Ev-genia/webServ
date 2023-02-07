/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:24:49 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/07 16:51:26 by mlarra           ###   ########.fr       */
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
	// FD_ZERO(&_fdSet);
	FD_ZERO(&_fdReadSave);
	FD_ZERO(&_fdWriteSave);
	_maxFd = 0;
	for (std::size_t i = 0; i < _servers->size(); i++)
	{
		(*_servers)[i].initSocket();
		FD_SET((*_servers)[i].getSocketFd(), &_fdReadSave);
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

void	Handler::process(Client *client)//, Config & conf)
{
	// Response		response;
	// std::string		recvd = "";

	if (client->request.find("Transfer-Encoding: chunked") != std::string::npos &&
		client->request.find("Transfer-Encoding: chunked") < client->request.find("\r\n\r\n"))
		processChunk(client);
	else if (client->request != "")
	{
		Request	request(client->request);
// std::cout << "Handler::process|request.getMethod(): " << request.getMethod() << std::endl;
		if (request.getRet() != 200)
			request.setMethod("GET");
std::cout << "end request" << std::endl;
		ResponseConfig responseConf(client->getServerRef(),  request);
		
		Response		response;
std::cout << "response start" << std::endl;

		response.call(request, responseConf);
// std::cout << "response call end" << std::endl;

		client->setResponse(response.getResponse());
std::cout << "Handler::process| response.getResponse(): " << response.getResponse() << std::endl;
std::cout << "client->setResponse end" << std::endl;
		// _requests.erase(socket);
		// _requests.insert(std::make_pair(socket, response.getResponse()));
	}
}

void	Handler::serverRun()
{
	int				ret;
	char			*buffer = (char *)malloc(10000001);
	int				fdClient;
	// struct timeval	timeout;

	while (true)
	{
		_fdRead = _fdReadSave;
		_fdWrite = _fdWriteSave;
		select(_maxFd + 1, &_fdRead, &_fdWrite, 0, 0);
		//проход по серверам
		for (std::size_t i = 0; /*ret &&*/ i < _servers->size(); i++)
		{
			int	serverFd = (*_servers)[i].getSocketFd();

			if (FD_ISSET(serverFd, &_fdRead))
			{
				Client *client = new Client(serverFd, (*_servers)[i]);//, i);
				client->acceptClient();
				FD_SET(client->getFd(), &_fdReadSave);
				_clients.push_back(client);
				if (client->getFd() > _maxFd)
					_maxFd = client->getFd();
			}
		}
//проход по читающим fd
		for (std::vector<Client *>::iterator it = _clients.begin(); /*ret &&*/ it != _clients.end(); it++)
		{
			fdClient = (*it)->getFd();
			if (FD_ISSET(fdClient, &_fdRead))
			{
				if (ret > 0)
				{
					ret = recv(fdClient, buffer, RECV_SIZE - 1, 0);
					buffer[ret] = 0;
					(*it)->request += buffer;
					memset(buffer, 0, RECV_SIZE);
				}
				else if (ret == 0)
				{
					FD_CLR(fdClient, &_fdReadSave);
					FD_CLR(fdClient, &_fdWriteSave);
					delete (*it);
					_clients.erase(it);
					break;
				}
				if ((*it)->request.find("\r\n\r\n") != std::string::npos)
				{
					FD_SET(fdClient, &_fdWriteSave);
					FD_CLR(fdClient, &_fdReadSave);
				}
				else
					break;
				process(*it);
			}

//проход по пишущим fd
			if (FD_ISSET(fdClient, &_fdWrite))
			{
				ret = send(fdClient, (*it)->getResponse().c_str(), (*it)->getResponse().size(), 0);
				if (ret <= 0)
				{
					FD_CLR(fdClient, &_fdWriteSave);
					FD_CLR(fdClient, &_fdReadSave);
					delete *it;
					_clients.erase(it);
					break;
				}
				if ((unsigned long)ret < (*it)->getResponse().length())
				{
					(*it)->setResponse((*it)->getResponse().substr(ret));
				}
				else
				{
					FD_CLR(fdClient, &_fdWriteSave);
					(*it)->setResponse("");
					delete *it;
					_clients.erase(it);
					break;
				}
			}
			//check timeout
			// memset(&timeout, 0, sizeof(timeout));
			// gettimeofday(&timeout, 0);
			// if ((FD_ISSET(fdClient, &_fdRead)) && (*it)->getTime() - timeout.tv_sec > 10)
			// {
			// 	FD_CLR(fdClient, &_fdReadSave);
			// 	FD_CLR(fdClient, &_fdWriteSave);
			// 	delete *it;
			// 	_clients.erase(it);
			// 	break;
			// }
		}
	}
}
