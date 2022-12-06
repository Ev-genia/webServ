/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:23:51 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/06 11:34:38 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include "webserv.hpp"

class Server;

class Handler
{
private:
	std::vector<Server>*	_servers;
	fd_set					_fdReadSave;
	// fd_set					_fdRead;
	// fd_set					_fdWriteSave;
	// fd_set					_fdWrite;
	std::vector<int>		_fds;
	int						_maxFd;
public:
	Handler(std::vector<Server> *);
	~Handler();
	void	initFds();
	void	serverRun();
};


#endif
