/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:24:11 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 11:31:49 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# define RECV_SIZE 2048
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
// # include <sys/time.h>

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


typedef  std::map<std::string, std::string> strStrMap;
typedef  std::pair<std::string, std::string> strStrPair;
typedef  std::map<std::string, std::string>::iterator strStrMapIteraror;
typedef  std::pair<std::string, bool> strBoolPair;

#endif
