/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/06 12:50:10 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/13 15:28:40 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CLIENT_HPP
# define CLIENT_HPP

# include "webserv.hpp"

class Client
{
private:
	int					_fd;
	int					_serverFd;
	struct sockaddr_in	_clientAddrIn;
	std::string			_ipAddress;
	std::string			_response;
	// struct timeval		_timeout;
public:
	std::string	request;
	Client(int);
	~Client();
	int			getFd() const;
	void		acceptClient();
	std::string	getResponse() const;
	std::string	getIpAddress() const;
};


#endif