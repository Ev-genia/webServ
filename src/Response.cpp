/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/07 16:10:00 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"

Response::Response()
{}

Response::~Response(){}

void	Response::call(Request &request, ResponseConfig &responseConf)
{
	_errorMap = responseConf.getErrorPage();
	_isAutoIndex = responseConf.getAutoIndex();
	_code = request.getRet();
	_hostPort = responseConf.getHostPort();
	_path = responseConf.getPath();

	if (responseConf.getAllowedMethods().find(request.getMethod()) == responseConf.getAllowedMethods().end())
		_code = 405;
	else if (responseConf.getBodySize() < request.getBody().size())
		_code = 413;
	if (_code == 405 || _code == 413)
	{
		ResponseHeader	head;

		_response = head.notAllowed(responseConf.getAllowedMethods(), responseConf.getContentLocation(),
				 _code) + "\r\n";
		return ;
	}
	(this->*Response::_method[request.getMethod()])(request, responseConf);
}

std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	Response::_method = Response::initMetods();

std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	Response::initMetods()
{
	std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	methodsMap;

	methodsMap["GET"] = &Response::methodGet;
	methodsMap["POST"] = &Response::methodPost;
	// methodsMap["DELETE"] = &Response::methodDelete;

	return (methodsMap);
}

std::string	Response::readHtml(const std::string &enterPath)
{
	std::ofstream		fileStream;
	std::stringstream	strStream;

	if (pathIsFile(enterPath))
	{
		fileStream.open(enterPath.c_str(), std::ifstream::in);
		if (fileStream.is_open() == false)
			return ("<!DOCTYPE html>\n<html><title>40404</title><body>There was an error finding your error page</body></html>\n");
		strStream << fileStream.rdbuf();
		fileStream.close();
		_type = "text/html";
		return (strStream.str());
	}
	else
		return ("<!DOCTYPE html>\n<html><title>40404</title><body>There was an error finding your error page</body></html>\n");
}

int	Response::readContent(Request &request)
{
	std::ifstream		fileStream;
	std::stringstream	strStream;

	_response = "";

	if (pathIsFile(_path))
	{
		fileStream.open(_path.c_str(), std::ifstream::in);
		if (fileStream.is_open() == false)
		{
			_response = readHtml(_errorMap[403]);
			return (403);
		}
		strStream << fileStream.rdbuf();
		_response = strStream.str();
		fileStream.close();
	}
	else if (_isAutoIndex && pathIsDir(_path.c_str()))
	{
std::cout << "Response::readContent|_isAutoIndex| _path: " << _path << std::endl;
		strStream << getPage(_path.c_str(), to_string(_hostPort->host), _hostPort->port, request);
		_response = strStream.str();
		_type = "text/html";
	}
	else
	{
std::cout << "Response::readContent|else| _path: " << _path << std::endl;
		_response = readHtml(_errorMap[404]);
		return (404);
	}
	return (200);
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
	{
		_code = readContent(request);
	}
	else
		_response = readHtml(_errorMap[_code]);
	// if (_code == 500)
	// 	_response = readHtml(_errorMap[_code]);
	_response = head.getHeader(_response.size(), _path, _code, _type, responseConf.getContentLocation()) + "\r\n" + _response;
std::cout << "Response::methodGet| _type: " << _type << std::endl;
std::cout << "Response::methodGet| _response: " << _response << std::endl;
}

std::string	Response::getResponse()
{
	return (_response);
}

void	Response::methodPost(Request & request, ResponseConfig &responseConf)
{
	ResponseHeader	head;

	if (responseConf.getCgiExec() != "")
	{
		CgiHandler	cgi(request, responseConf);
		size_t		i = 0;
		size_t		j = _response.size() - 2;

		_response = cgi.executeCgi(responseConf.getCgiExec());
		while (_response.find("\r\n\r\n", i) != std::string::npos || _response.find("\r\n", i) == i)
		{
			std::string	str = _response.substr(i, _response.find("\r\n", i) - i);
			if (str.find("Status: ") == 0)
				_code = std::atoi(str.substr(8, 3).c_str());
			else if (str.find("Content-type: ") == 0)
				_type = str.substr(14, str.size());
			i += 2;
		}
		while (_response.find("\r\n") == j)
			j -=2;
		_response = _response.substr(i, j - i);
	}
}
