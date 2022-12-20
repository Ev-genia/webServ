/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/20 17:38:41 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

void	Request::resetRequestMap()
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

Request::Request(const std::string str): _method(""), _version(""), _path(""), _body(""), _ret(200)
{
	resetRequestMap();
	_envForCgi.clear();
	parseRequest(str);
	if (_ret != 200)
		std::cerr << "Error init request" << std::endl;
}

/*
GET / HTTP/1.1\nHost: developer.mozilla.org\nAccept-Language: fr\r\n\r\n<body>
*/

// std::string	&Request::pop(std::string &str)
void	Request::pop(std::string &str)
{
	if (str.size())
		str.resize(str.size() - 1);
	// return (str);
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
	i = line.find_first_of(' ', i);
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
	if (_version != "1.1")
	{
		_ret = 400;
		std::cerr << "Error in http request: Bad http version (" << _version << ")" << std::endl;
		return ;
	}
	checkMethod();
}

void	Request::readPath(const std::string &line, size_t i)
{
	size_t	j;

	j = line.find_first_of(' ', i);
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
	_path.assign(line, j, i - j);
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
	readPath(line, i);
}

std::string	&Request::strip(std::string &str, char c)
{
	size_t	i;

	if (!str.size())
		return (str);
	i = str.size();
	while (i && str[i - 1] == c)
		i--;
	str.resize(i);
	for (i = 0; str[i] == c; i++);
	str = str.substr(i, std::string::npos);
	return (str);
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

std::vector<std::string>	Request::split(const std::string &str, char c)
{
	std::vector<std::string>	tokens;
	std::istringstream			tokenStream(str);
	std::string					token;

	while (std::getline(tokenStream, token, c))
		tokens.push_back(token);
	return (tokens);
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
		
	}
}

void	Request::parseRequest(const std::string &enterRequest)
{
	size_t		poz = 0;
	std::string	line;
	std::string	key;
	std::string	value;
	
	line = nextLine(enterRequest, poz);
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
	
	// this->setLang();
	setBody(enterRequest.substr(poz, std::string::npos));
	// this->setBody(str.substr(i, std::string::npos));
	// this->findQuery();
	
	_ret = 200;
}

Request::~Request()
{
}

int	Request::getRet() const
{
	return (_ret);
}

void	Request::setMethod(const std::string enterMethod)
{
	_method = enterMethod;
}

std::map<std::string, std::string>	&Request::getRequestMap()
{
	return _requestMap;
}
