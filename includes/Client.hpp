/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:50:10 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/25 15:05:56 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class Server;

class Client
{
private:
	int					_fd;
	int					_serverFd;
	struct sockaddr_in	_clientAddrIn;
	std::string			_ipAddress;
	std::string			_response;
	// int					_servIndex;
	// struct timeval		_timeout;
	Server				&_serverRef;
public:
	std::string	request;
	Client(int, Server &);//int);
	~Client();
	int					getFd() const;
	int					getServerFd() const;
	void				acceptClient();
	const std::string	&getResponse() const;
	const std::string	&getIpAddress() const;
	const Server		&getServerRef() const;
};


#endif