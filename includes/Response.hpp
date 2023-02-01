/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:25:53 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 11:38:08 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSE_HPP
# define RESPONSE_HPP
# include "webserv.hpp"

typedef  std::map<std::string, std::string> strStrMap;

class Server;
class RequestConfig;

class Response
{
private:
	std::string	_response;
	strStrMap	_requestMap;
	Server		_server;
	Client 		*_client;

	void		methodGet(Request &, RequestConfig &);
	void		methodPost(Request &, RequestConfig &);
	void		methodDelete(Request &, RequestConfig &);
public:
	Response(strStrMap requestMap, Server &server, Client *client);
	~Response();

	static std::map<std::string, void (Response::*)(Request &, RequestConfig &)>	initMetods();
};

#endif