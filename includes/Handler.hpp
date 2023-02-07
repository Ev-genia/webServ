/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:23:51 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/06 17:41:15 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

// # define RECV_SIZE 2048
# include "webserv.hpp"

class Server;
class Client;
// class Response;

class Handler
{
private:
	std::vector<Server>*	_servers;
	std::vector<Client *>	_clients;
	// fd_set					_fdSet;
	fd_set					_fdReadSave;
	fd_set					_fdRead;
	fd_set					_fdWriteSave;
	fd_set					_fdWrite;
	// std::vector<int>		_fds;
	int						_maxFd;
public:
	Handler(std::vector<Server> *);
	~Handler();
	void	initFds();
	void	serverRun();
	void	process(Client *);
	void	processChunk(Client *);

};


#endif
