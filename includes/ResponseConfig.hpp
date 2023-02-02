/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:29:05 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/02 17:46:23 by mlarra           ###   ########.fr       */
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
	std::string						_contentLocation; //???????????????? что с этим делать?
	std::string						_locationPath;
	std::string						_path; //полный путь к исполняемому файлу  cgi 
	std::map<int, std::string>		_errorPage;
	unsigned long					_body_size; // max size for the client body, defaults to 8 000??
	std::string						_lang;
	std::set<std::string>			_method_allowed;
	bool							_autoindex;
	std::string						_exec_cgi;
	std::string						_root;
	std::vector<std::string>		_extension_cgi;
	struct s_listen					&_hostPort;
	Server							&_server;
	Request							&_request;
	void							initErrorPages();

public:
	ResponseConfig(Server &server, Request &request);
	~ResponseConfig();
	Server								&getServer() const;
	const std::string					&getLocationPath() const;
	const std::string					&getPath() const;
	const bool							&getAutoIndex() const;
	struct s_listen						&getHostPort() const;
	std::string							&getCgiExec();
	std::set<std::string>				getAllowedMethods() const;
	unsigned long						getBodySize() const;
	const std::string					&getContentLocation() const;
	const std::map<int, std::string>	&getErrorPage() const;
	std::string							removeSlashes(const std::string &);
	std::vector<std::string>			makeVector(std::string extensionString, const char delim);
	std::set<std::string>				makeSet(std::vector<std::string>);
};


# endif
