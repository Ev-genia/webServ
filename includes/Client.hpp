/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:50:10 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/09 00:54:47 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class Server;
class Request;

class Client
{
private:
	int					_fd;//файловый дескриптор клиента
	int					_serverFd;
	struct sockaddr_in	_clientAddrIn;
	std::string			_ipAddress;
	std::string			_response;
	struct timeval		_timeout;
	Server				&_serverRef;
public:
	std::string			request;
	Client(int, Server &);
	~Client();
	int					getFd() const;
	int					getServerFd() const;
	void				acceptClient();
	const std::string	&getResponse() const;
	const std::string	&getIpAddress() const;
	Server				&getServerRef() const;
	void				setResponse(std::string);
	int					getTime();

	int					_readyToSend;
	int					_sendEnd;
	Request				*requestObj;
};


#endif