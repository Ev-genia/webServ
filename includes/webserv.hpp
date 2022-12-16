/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:24:11 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/16 16:53:22 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
# include <arpa/inet.h>
// # include <event.h>
# include <unistd.h>
# include <fcntl.h>
# include <map>
# include <vector>
// # include <sys/time.h>

# include "Server.hpp"
# include "utils.hpp"
# include "Handler.hpp"
# include "Config.hpp"
# include "Client.hpp"
# include "Location.hpp"
# include "Request.hpp"
# include "Response.hpp"

typedef  std::map<std::string, std::string> strStrMap;
typedef  std::pair<std::string, std::string> strStrPair;
typedef  std::map<std::string, std::string>::iterator strStrMapIteraror;
typedef  std::pair<std::string, bool> strBoolPair;

#endif
