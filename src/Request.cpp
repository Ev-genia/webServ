/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/09 11:57:52 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

Request::Request()
{}

void	Request::initRequestMap()
{
	_requestMap.clear();
	// _requestMap["Accept-Charsets"] = "";
	// _requestMap["Accept-Language"] = "";
	_requestMap["Allow"] = "";
	// _requestMap["Auth-Scheme"] = "";
	_requestMap["Authorization"] = "";
	_requestMap["Content-Language"] = "";
	_requestMap["Content-Length"] = "";
	_requestMap["Content-Location"] = "";
	_requestMap["Content-Type"] = "";
	_requestMap["Date"] = "";
	_requestMap["Host"] = "";
	_requestMap["Last-Modified"] = "";
	_requestMap["Location"] = "";
	_requestMap["Referer"] = "";
	_requestMap["Retry-After"] = "";
	_requestMap["Server"] = "";
	_requestMap["Transfer-Encoding"] = "";
	_requestMap["User-Agent"] = "";
	_requestMap["Www-Authenticate"] = "";
	_requestMap["Connection"] = "Keep-Alive";
}

Request::Request(const std::string &str): _method(""), _version(""), _uri(""),
	_body(""), _query(""), _ret(200), _boundary(), _endBoundary(""), _fullBuffer(""),
	_endBody(false), _fileName("")
{
	initRequestMap();
	_envForCgi.clear();
	parseRequest(str);
	if (_ret != 200)
		std::cerr << "Error init request" << std::endl;
}

Request	&Request::operator=(const Request &rhs)
{
	_method = rhs._method;
	_version = rhs._version;
	_uri = rhs._uri;
	_requestMap = rhs.getRequestMap();
	_body = rhs._body;
	_query = rhs._query;
	_envForCgi = rhs.getEnvForCgi();
	_ret = rhs._ret;

	return (*this);
}

std::string	Request::nextLine(const std::string &str, size_t &i)
{
	std::string	ret;
	size_t		j;

	if (i == std::string::npos)
		return ("");
	j = str.find_first_of('\n', i);
	ret = str.substr(i, j - i);
	if (ret[ret.size() - 1] == '\r')
		pop(ret);
	if (j == std::string::npos)
		i = j;
	else
		i = j + 1;
	return (ret);
}

std::vector<std::string>	Request::initMethods()
{
	std::vector<std::string>	methods;

	methods.push_back("GET");
	methods.push_back("POST");
	methods.push_back("DELETE");
	return (methods);
}

std::vector<std::string>	Request::availableMethods = Request::initMethods();

void	Request::checkMethod()
{
	for (size_t i = 0; i < availableMethods.size(); i++)
	{
		if (availableMethods[i] == _method)
			return ;
	}
	std::cerr << "Invalid method requested" << std::endl;
}

void	Request::readVersion(const std::string &line, size_t i)
{
	i = line.find_first_not_of(' ', i);
	if (i == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No http version" << std::endl;
		return ;
	}
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T'
			&& line[i + 3] == 'P' && line[i + 4] == '/')
	{
		_version.assign(line, i + 5, 3);
	}
	if (_version != "1.0" && _version != "1.1")
	{
		_ret = 400;
		std::cerr << "Error in http request: Bad http version (" << _version << ")" << std::endl;
		return ;
	}
	checkMethod();
}

void	Request::readUri(const std::string &line, size_t i)
{
	size_t	j;
	j = line.find_first_not_of(' ', i);
	if (j == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No PATH/URI" << std::endl;
		return ;
	}
	i = line.find_first_of(' ', j);
	if (i == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No http version" << std::endl;
		return ;
	}
	_uri.assign(line, j, i - j);
	readVersion(line, i);
}

void	Request::readFirstLine(const std::string &str)
{
	size_t		i;
	std::string	line;

	i = str.find_first_of('\n');
	line = str.substr(0, i);
	i = line.find_first_of(' ');
	if (i == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No space after metod" << std::endl;
		return ;
	}
	_method.assign(line, 0, i);
// std::cout << "Request::readFirstLine|_metod: " << _method << std::endl;
// std::cout << "Request::readFirstLine| i: " << i << std::endl;
	readUri(line, i);
}

std::string	Request::readKey(const std::string &src)
{
	std::string	dst;
	size_t		i;

	i = src.find_first_of(':');
	dst.append(src, 0, i);
	return (strip(dst, ' '));
}

std::string	Request::readValue(const std::string &src)
{
	std::string	dst;
	size_t		i;

	i = src.find_first_of(':');
	i = src.find_first_not_of(' ');
	if (i != std::string::npos)
		dst.append(src, i, std::string::npos);
	return (strip(dst, ' '));
}

void	Request::setBody(const std::string &line)
{
	char	ends[] = {'\n', '\r'};

	_body.assign(line);
	for (int i = 0; i < 4; i++)
	{
		if (_body.size() > 0 && _body[_body.size() - 1] == ends[i % 2])
			pop(_body);
		else
			break;
	}
}

void	Request::findQuery()
{
	size_t	i;

	i = _uri.find_first_of('?');
	if (i != std::string::npos)
	{
		_query.assign(_uri, i + 1, std::string::npos);
		_uri = _uri.substr(0, i);
	}
}

void	Request::createCgi()
{
	
}

void	Request::parseRequest(const std::string &enterRequest)
{
	size_t		poz = 0;
	std::string	line;
	std::string	key;
	std::string	value;

	// std::cout << "Request::parseRequest| enterRequest: " << std::endl;
	std::cout << "********REQUEST*********" << std::endl;
	std::cout << enterRequest << std::endl;
	line = nextLine(enterRequest, poz);
	std::cout << "******END REQUEST*******" << std::endl;
// std::cout << "Request::parseRequest|line: " << line << std::endl;
	readFirstLine(line);
	while (line != "\r" && line != "" && _ret != 400)
	{
		key = readKey(line);
		value = readValue(line);
		if (_requestMap.count(key))
			_requestMap[key] = value;
		// if (key.find("Secret") != std::string::npos)
		// 	_envForCgi[formatHeaderForCGI(key)] = value;
		line = nextLine(enterRequest, poz);
	}
	if (_requestMap["Www-Authenticate"] != "")
		_envForCgi["Www-Authenticate"] = _requestMap["Www-Authenticate"];
	_body = enterRequest.substr(poz, std::string::npos);
	findQuery();
}

Request::~Request()
{
}

const std::string	&Request::getMethod() const
{
	return (_method);
}

const std::string	&Request::getVersion() const
{
	return (_version);
}

const std::string	&Request::getUri() const
{
	return (_uri);
}

const std::map<std::string, std::string>	&Request::getRequestMap() const
{
	return (_requestMap);
}

const std::string	&Request::getBody() const
{
	return (_body);
}

const std::string	&Request::getQuery() const
{
	return (_query);
}

const std::map<std::string, std::string>	&Request::getEnvForCgi() const
{
	return (_envForCgi);
}

int	Request::getRet() const
{
	return (_ret);
}

void	Request::setMethod(const std::string enterMethod)
{
	_method = enterMethod;
}

// std::string	Request::getBoundary()
// {
// 	return (_boundary);
// }

// std::string	Request::getEndBoundary()
// {
// 	return (_endBoundary);
// }

std::string	Request::getFullBuffer()
{
	return (_fullBuffer);
}

bool	Request::getEndBody()
{
	return (_endBody);
}

// void	Request::setBoundary(std::string enterBoundary)
// {
// 	_boundary = enterBoundary;
// }

// void	Request::setEndBoundary(std::string enterEndBoundary)
// {
// 	_endBoundary = enterEndBoundary;
// }

// void	Request::appendFullBuffer(std::string enterAppend)
// {
// 	_fullBuffer.append(enterAppend);
// }

// void	Request::setEndBody(bool value)
// {
// 	_endBody = value;
// }

void	Request::bodyParsing()
{
	size_t	poz = 0;

	while (_fullBuffer.find(_endBoundary) != std::string::npos)
	{
		if ((poz = _fullBuffer.find("filename=")) != std::string::npos)
		{
			_fullBuffer.erase(0, poz + 10);
			_fileName = _fullBuffer.substr(0, _fullBuffer.find("\""));
			_fullBuffer.erase(0, _fullBuffer.find("\r\n\r\n") + 4);
		}
		size_t	pozEOF = _fullBuffer.find(_boundary);
		size_t	pozEnter = _fullBuffer.find("\r\n", pozEOF);
		std::ofstream	fout;

		fout.open(("www/server3/storage/" + _fileName).c_str(), std::ofstream::out);
		fout << _fullBuffer.substr(0, pozEnter);
		fout.close();
		_fullBuffer.erase(0, pozEOF + _boundary.length());
	}
	_fullBuffer = "";
}

void	Request::findBoundary()
{
	std::map<std::string, std::string>::iterator it = _requestMap.find("Content-Type");
	std::string	preBoundary;

	preBoundary = it->second.substr(it->second.find("boundary=") + 9);
	_boundary = preBoundary.substr(preBoundary.rfind('-') + 1);
	_endBoundary = _boundary + "--";
	if (_body != "")
	{
		_fullBuffer.append(_body);
		if (_fullBuffer.find(_endBoundary) != std::string::npos)
			_endBody = true;
		else
		{
			_fullBuffer.append("\r\n\r\n--" + preBoundary + "--");
			_endBody = true;
		}
	}
	_body = "";
	if (_endBody == true)
	{
		bodyParsing();
	}
}

std::string	Request::getFileName()
{
	return (_fileName);
}

