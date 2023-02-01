/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 01:03:29 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"

Response::Response(){}

Response::~Response(){}

void	Response::call(Request &request, ResponseConfig &responseConf)
{
	//_errorMap = responseConf.getErrorPage();
	_isAutoIndex = responseConf.getAutoIndex();
	_code = request.getRet();
	_hostPort.host = responseConf.getHostPort().host;
	_hostPort.port = responseConf.getHostPort().port;
	//_path = requestConf.getPath();

std::vector<std::string>::iterator it = responseConf.getAllowedMethods().begin();
	for(; it != responseConf.getAllowedMethods().end(); it++)
	{	if ((*it) == request.getMethod())
			_code = 405;
	}
}

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
