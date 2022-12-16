/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/15 17:39:11 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

Request::Request(const std::string str)
{
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

void	Request::readFirstLine(const std::string &line)
{
	
}

void	Request::parseRequest(const std::string &enterRequest)
{
	size_t	poz = 0;
	
	readFirstLine(nextLine(enterRequest, poz));


	_ret = 200;
}

Request::~Request()
{
}

int	Request::getRet() const
{
	return (_ret);
}

void	Request::setMethod(const std::string enterMetod)
{
	_metod = enterMetod;
}
