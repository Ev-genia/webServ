/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:29:05 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/25 17:25:07 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSECONFIG_HPP
# define RESPONSECONFIG_HPP

# include "webserv.hpp"

class Server;
class Request;

class ResponseConfig
{
private:
	std::string		_contentLocation;
	std::string		_path;
	std::string		_error_page;
	unsigned long	_body_size; // max size for the client body, defaults to 8 000??
	std::string		_lang;
	std::string		_method_allowed;
	std::string		_autoindex;
	std::string		_exec_cgi;
	std::string		__contentLocation; //???????????????? что с этим делать?

	std::vector<std::string>			_extension_cgi;
	std::string							_exec_cgi;
	Server			&_server;
	Request			&_request;

public:
	ResponseConfig(Server &server, Request &request);
	~ResponseConfig();
	Server				&getServer() const;
	const std::string	&getPath() const;

	std::string			removeSlashes(const std::string &);

	std::vector<std::string>	makeCgiVector(std::string extensionString, const char delim);
};


# endif
