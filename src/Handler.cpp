/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:24:49 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:02:28 by wcollen          ###   ########.fr       */
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

void	Handler::process(Client *client)//, Config & conf)
{
	 Response		response;
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
		
		ResponseConfig responseConf(client->getServerRef(),  request);

		response.call(request, responseConf);

		// client->setResponse(response.getResponse());

		// _requests.erase(socket);
		// _requests.insert(std::make_pair(socket, response.getResponse()));
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
		// struct timeval	timeout;

		FD_ZERO(&fdRead);
		FD_ZERO(&fdWrite);
		memcpy(&fdRead, &_fdSet, sizeof(_fdSet));
		memcpy(&fdWrite, &_fdSet, sizeof(_fdSet));
		ret = select(_maxFd + 1, &fdRead, &fdWrite, 0, 0);
		if (ret == -1)
			exitError("Select");
		if (ret > 0)
		{
			//проход по серверам
			for (std::size_t i = 0; i < _servers->size(); i++)
			{
				int	serverFd = (*_servers)[i].getSocketFd();

				if (FD_ISSET(serverFd, &fdRead))
				{
					Client *client = new Client(serverFd, (*_servers)[i]);//, i);
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
				char	buffer[RECV_SIZE] = {0};

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
					}
					else if (ret == -1)
					{
						FD_CLR(fdClient, &_fdSet);
						FD_CLR(fdClient, &fdRead);
						//? delete *it;
						_clients.erase(it);
						it = _clients.begin();//?
					}
					break;
				}
			}
			//проход по пишущим fd
			for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
			{
				fdClient = (*it)->getFd();

				if (FD_ISSET(fdClient, &fdWrite))
				{
std::cout << "(*it)->getResponse().c_str(): " << std::endl;
					ret = send(fdClient, (*it)->getResponse().c_str(), (*it)->getResponse().size(), 0);
					if (ret == -1)
					{
						close(fdClient);
						FD_CLR(fdClient, &_fdSet);
						_clients.erase(it);
						break;
					}
				}
			}
		//check timeout
		}
		else
		{
			std::cerr << "Problem with select" << std::endl;
			for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
			{
				close((*it)->getFd());
				//надо ли удалять реквесты и прочие строковые переменные клиента?
			}
			for (std::vector<Client *>::iterator it = _clients.begin(); it != _clients.end(); it++)
			{
				delete(*it);
				//надо ли удалять реквесты и прочие строковые переменные клиента?
			}
			_clients.clear();
			FD_ZERO(&_fdSet);
			for (std::vector<Server>::iterator it = (*_servers).begin(); it != (*_servers).end(); it++)
				FD_SET(it->getSocketFd(), &_fdSet);
		}
	}
}
