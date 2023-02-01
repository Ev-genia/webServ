/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:16:48 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

Request::Request()
{}

void	Request::initRequestMap()
{
	_requestMap.clear();
	_requestMap["Accept-Charsets"] = "";
	_requestMap["Accept-Language"] = "";
	_requestMap["Allow"] = "";
	_requestMap["Auth-Scheme"] = "";
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

Request::Request(const std::string &str): _method(""), _version(""), _uri(""), _body(""), _query(""), _ret(200)
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

/*
GET / HTTP/1.1\nHost: developer.mozilla.org\nAccept-Language: fr\r\n\r\n<body>
*/

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
// std::cout << "Request::readVersion|line[i]: " << &line[i] << std::endl;
// std::cout << "Request::readVersion| i: " << i << std::endl;
	if (line[i] == 'H' && line[i + 1] == 'T' && line[i + 2] == 'T'
			&& line[i + 3] == 'P' && line[i + 4] == '/')
	{
		_version.assign(line, i + 5, 3);
// std::cout << "Request::readVersion|HTTP version: " << _version << std::endl;
	}
	if (_version != "1.0" && _version != "1.1")
	{
		_ret = 400;
		std::cerr << "Error in http request: Bad http version (" << _version << ")" << std::endl;
		return ;
	}
std::cout << "Request::readVersion|_version: " << _version << std::endl;
	checkMethod();
}

void	Request::readUri(const std::string &line, size_t i)
{
	size_t	j;
// std::cout << "Request::readPath|line(enter): " << line << std::endl;
	j = line.find_first_not_of(' ', i);
// std::cout << "Request::readPath| j: " << j << std::endl;
	if (j == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No PATH/URI" << std::endl;
		return ;
	}
	i = line.find_first_of(' ', j);
// std::cout << "Request::readPath| i: " << i << std::endl;
	if (i == std::string::npos)
	{
		_ret = 400;
		std::cerr << "Error in http request: No http version" << std::endl;
		return ;
	}
	_uri.assign(line, j, i - j);
std::cout << "Request::readUri|_uri: " << _uri << std::endl;
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
std::cout << "Request::readFirstLine|_metod: " << _method << std::endl;
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

// void	Request::setLang()
// {
// 	std::string					header;
// 	std::vector<std::string>	token;
// 	size_t						i;

// 	header = _requestMap["Accept-Language"];
// 	if (header != "")
// 	{
// 		token = split(header, ',');
// 		for (std::vector<std::string>::iterator it = token.begin(); it != token.end(); it++)
// 		{
// 			float		weight = 0.0;
// 			std::string	lang;

// 			lang = (*it).substr(0, (*it).find_first_of('-'));
// 			strip(lang, ' ');
// 			i = lang.find_last_of(';');
// 			if (i != std::string::npos)
// 				weight = atof();
// 		}
// 	}
// }

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
std::cout << "Request::findQuery| _uri: " << _uri << std::endl;
std::cout << "Request::findQuery| _query: " << _query << std::endl;
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
	
	line = nextLine(enterRequest, poz);
std::cout << "-----------------------------------" << std::endl;
std::cout << "Request::parseRequest|line: " << line << std::endl;
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
	
	// setLang();
	setBody(enterRequest.substr(poz, std::string::npos));
	findQuery();
	// if (_uri.find("cgi_bin") != std::string::npos)
	// 	createCgi();
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
