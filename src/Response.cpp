/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 11:49:28 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"

Response::Response(strStrMap requestMap, Server &server, Client *client)
	:_requestMap(requestMap), _server(server), _client(client){}

Response::~Response(){}

std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	Response::initMetods()
{
	std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	methodsMap;

	methodsMap["GET"] = &Response::methodGet;
	methodsMap["POST"] = &Response::methodPost;
	methodsMap["DELETE"] = &Response::methodDelete;

	return (methodsMap);
}

void	Response::methodGet(Request &request, RequestConfig &requestConf)
{}
