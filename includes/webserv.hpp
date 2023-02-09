/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:24:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/08 01:52:36 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define RECV_SIZE 5000
# define CGI_BUFF_SIZE 2048

# include <iostream>
// # include <istream>
# include <sstream>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
// # include <event.h>
# include <unistd.h>
# include <fcntl.h>
# include <map>
# include <vector>
# include <set>
 # include <sys/time.h>
# include <sys/stat.h>
# include <fstream>
# include <dirent.h>
# include <sys/types.h>

# include "Server.hpp"
# include "utils.hpp"
# include "Handler.hpp"
# include "Config.hpp"
# include "Client.hpp"
# include "Location.hpp"
# include "Request.hpp"
# include "Response.hpp"
# include "ResponseConfig.hpp"
# include "ResponseHeader.hpp"
# include "CgiHandler.hpp"

//server's host and port
// typedef struct s_listen
// {
// 	int				port;
// 	in_addr_t		host;
// }					t_listen;
// };

typedef  std::map<std::string, std::string> strStrMap;
typedef  std::pair<std::string, std::string> strStrPair;
typedef  std::map<std::string, std::string>::iterator strStrMapIteraror;
typedef  std::pair<std::string, bool> strBoolPair;

#endif
