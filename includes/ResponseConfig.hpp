/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseConfig.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 16:29:05 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/24 16:16:56 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSECONFIG_HPP
# define RESPONSECONFIG_HPP

# include "webserv.hpp"

class ResponseConfig
{
private:
	std::string		_contentLocation;
	std::string		_path;
	std::string		_error_page;// error page redirections
	unsigned long	_client_body_buffer_size; // max size for the client body, defaults to 8 000??
	Server			&_server;
	Request			&_request;
public:
	ResponseConfig(Server &server, Request &request);
	~ResponseConfig();
	Server				&getServer() const;
	const std::string	&getPath() const;
	std::string			removeSlashes(const std::string &);
};




# endif