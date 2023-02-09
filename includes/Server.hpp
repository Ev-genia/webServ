/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:42 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/09 12:00:44 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "webserv.hpp"

class Location;
class Client;

// //server's host and port
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
	struct s_listen						_listen;
	int									_reuse;
public:
	// Server();
	~Server();
	bool								getAutoIndex() const;
	std::map<std::string, std::string>	&getParams();
	s_listen							&getListen();
	int									getSocketFd() const;
	std::vector<Location>				&getLocations();
	void								initSocket();
	void								setAddr();
	void								setAutoindex(bool index);
	void								setListen(struct s_listen value);
};



#endif