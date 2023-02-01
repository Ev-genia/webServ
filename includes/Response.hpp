/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:25:53 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 12:09:18 by mlarra           ###   ########.fr       */
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
	std::string	_response;
	strStrMap	_requestMap;
	Server		_server;
	Client 		*_client;

	std::string					_response;
	std::string					_path;
	int							_code;
	std::string					_type;
	bool						_isAutoIndex;
	t_listen					_hostPort;
	std::map<int, std::string>	_errorMap; // ??????????

	void		methodGet(Request &, ResponseConfig &);
	void		methodPost(Request &, ResponseConfig &);
	void		methodDelete(Request &, ResponseConfig &);

public:
	Response();
	~Response();

	void			call(Request &request, ResponseConfig &responseConf);


	static std::map<std::string, void (Response::*)(Request &, ResponseConfig &)>	initMetods();
};

#endif