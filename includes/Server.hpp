/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:42 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/16 17:35:51 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

class Location;
class Client;

//server's host and port
typedef struct s_listen
{
	int				port;
	in_addr_t		host;
}					t_listen;

class Server
{
private:
	int									_socketFd;
	bool								_autoindex;
	std::map<std::string, std::string>	_params;
	std::vector<Location>				_locations;
	struct sockaddr_in					_addrIn;
	std::vector<t_listen>				_listens;
	// int									_reuse;
public:
	Server();
	~Server();
	bool								getAutoIndex() const;
	std::map<std::string, std::string>	&getParams();
	std::vector<t_listen>				&getListens();
	int									getSocketFd() const;
	std::vector<Location>				getLocations() const;
	void								initSocket();
	void								setAddr();
};



#endif