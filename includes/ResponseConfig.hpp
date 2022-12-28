/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:29:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/28 17:58:05 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REPONSECONFIG_HPP
# define RESPONSECONFIG_HPP

# include "webserv.hpp"

class ResponseConfig
{
private:
	std::string		_contentLocation;
	std::string		_path;
	std::string		_error_page;// error page redirections
	unsigned long	_client_body_buffer_size; // max size for the client body, defaults to 8 000??
	// t_listen		_hostPort;
	Server			&_server;
	Request			&_request;
public:
	ResponseConfig(Server &server, Request &request);
	// ResponseConfig(Config &config, Request &request);
	~ResponseConfig();
	// const t_listen	&getHostPort() const;
	// void			setHostPort(const t_listen);
	Server			&getServer() const;
};




# endif