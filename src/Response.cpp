/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 16:01:14 by mlarra           ###   ########.fr       */
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

std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	Response::initMetods()
{
	std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	methodsMap;

	methodsMap["GET"] = &Response::methodGet;
	methodsMap["POST"] = &Response::methodPost;
	methodsMap["DELETE"] = &Response::methodDelete;

	return (methodsMap);
}

void	Response::methodGet(Request &request, ResponseConfig &responseConf)
{
	ResponseHeader	head;
	size_t		i = 0;
	size_t		j = _response.size() - 2;
	std::string	tmpString;

	if (responseConf.getCgiExec() != "")
	{
		CgiHandler	cgi(request, responseConf);

		_response = cgi.executeCgi(responseConf.getCgiExec());
		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
		{
			tmpString = _response.substr(i, _response.find("\r\n", i) - i);
			if (tmpString.find("Status: ") == 0)
				_code = std::atoi(tmpString.substr(8, 3).c_str());
			else if (tmpString.find("Content-type: ") == 0)
				_type = tmpString.substr(14, tmpString.size());
			i += tmpString.size() + 2;
		}
		while (_response.find("\r\n", j) == j)
			j -= 2;
		_response = _response.substr(i, j - i);
	}
	else if (_code == 200)
		_code = readContent();
	else
		_response = readHtml(_errorMap[_code]);
	// if (_code == 500)
	// 	_response = this->readHtml(_errorMap[_code]);
	_response = head.getHeader(_response.size(), _path, _codde, _type, responseConf.getContentLication()) + "\r\n" + _response;
}
