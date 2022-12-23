/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:26:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/23 23:50:49 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CgiHandler.hpp"

CgiHandler::CgiHandler(Request &request): _body(request.getBody())
{
	initEnv(request);
}

void	CgiHandler::initEnv(Request &request)
{
	std::map<std::string, std::string>	headers;

	headers = request.getRequestMap();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		_env["AUTH_TYPE"] = headers["Auth-Scheme"];
	_env["REDIRECT_STATUS"] = "200";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	// _env["SCRIPT_NAME"] = 
	// _env["SCRIPT_FILENAME"] = 
	_env["REQUEST_METHOD"] = request.getMethod();
	_env["CONTENT_LENGHT"] = std::to_string(_body.length());
	_env["CONTENT_TYPE"] = headers["Content-type"];
	_env["PATH_INFO"] = request.getUri();
	_env["PATH_TRANSLATED"] = request.getUri();
	_env["QUERY_STRING"] = request.getQuery();
	// _env["REMOTEaddr"] = 
	_env["REMOTE_IDENT"] = headers["Authorization"];
	_env["REMOTE_USER"] = headers["Authorization"];
	_env["REQUEST_URI"] = request.getUri() + request.getQuery();
	if (headers.find("Hostname") != headers.end())
		_env["SERVER_NAME"] = headers["Hostname"];
	else
		_env["SERVER_NAME"] = _env["REMOTEaddr"];
	// _env["SERVER_PORT"] = 
	_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	_env["SERVER_SOFTWARE"] = "Webserv/1.0";
	// _env.insert();
}