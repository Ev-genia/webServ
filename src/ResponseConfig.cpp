/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:23:11 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/30 13:47:24 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ResponseConfig.hpp"

ResponseConfig::ResponseConfig(Server &server, Request &request): _server(server), _request(request)
{}

ResponseConfig::~ResponseConfig()
{}

Server	&ResponseConfig::getServer() const
{
	return (_server);
}

const std::string	&ResponseConfig::getPath() const
{
	return (_path);
}
