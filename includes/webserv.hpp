/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:24:11 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/19 21:06:21 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEBSERV_HPP
# define WEBSERV_HPP

# include <iostream>
# include <sys/socket.h>
# include <sys/select.h>
# include <netinet/in.h>
// # include <event.h>
# include <unistd.h>
# include <fcntl.h>
# include <map>
# include <vector>
// # include <sys/time.h>
# include <arpa/inet.h>
# include <istream>


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
