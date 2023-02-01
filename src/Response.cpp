/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:25:44 by wcollen          ###   ########.fr       */
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

	if (responseConf.getAllowedMethods().find(request.getMethod()) == responseConf.getAllowedMethods().end())
		_code = 405;
	else if (responseConf.getBodySize() < request.getBody().size())
		_code = 413;
	if (_code == 405 || _code == 413)
	{
		ResponseHeader	head;

		// _response = head.notAllowed(responseConf.getAllowedMethods(), responseConf.getContentLocation(),
		// 		 _code, responseConf.getLang()) + "\r\n";
		return ;
	}
	(this->*Response::_method[request.getMethod()])(request, responseConf);
}

