/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:25:53 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/31 23:22:21 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "webserv.hpp"

typedef  std::map<std::string, std::string> strStrMap;

class Server;

class Response
{
private:
	private:
	std::string					_response;
	std::string					_path;
	int							_code;
	std::string					_type;
	bool						_isAutoIndex;
	t_listen					_hostPort;
	std::map<int, std::string>	_errorMap; // ??????????
public:
	Response();
	~Response();

	void			call(Request &request, ResponseConfig &responseConf);

};

#endif