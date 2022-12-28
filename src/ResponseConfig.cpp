/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/28 17:58:46 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

// ResponseConfig::ResponseConfig(Config &config, Request &request){}
ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{}

ResponseConfig::~ResponseConfig()
{}

// const t_listen	&ResponseConfig::getHostPort() const
// {
// 	return (_hostPort);
// }

// void	ResponseConfig::setHostPort(const t_listen enterHostPort)
// {
// 	_hostPort.host = enterHostPort.host;
// 	_hostPort.port = enterHostPort.port;
// }

Server	&ResponseConfig::getServer() const
{
	return (_server);
}