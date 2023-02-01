/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:50:10 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:10:01 by wcollen          ###   ########.fr       */
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
	Server				&getServerRef() const;
	void				setResponse(std::string);
};


#endif