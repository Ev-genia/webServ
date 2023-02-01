/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:20 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/27 22:59:20 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "webserv.hpp"

class Request
{
private:
	std::string							_method;
	std::string							_version;
	std::string							_uri;
	std::map<std::string, std::string>	_requestMap;
	std::string							_body;
	std::string							_query;
	std::map<std::string, std::string>	_envForCgi;
	int									_ret;
	static std::vector<std::string>		availableMethods;
	static std::vector<std::string>		initMethods();
	void								initRequestMap();
	void								parseRequest(const std::string &);
	void								readFirstLine(const std::string &);
	void								readUri(const std::string &, size_t);
	void								readVersion(const std::string &, size_t);
	void								checkMethod();
	std::string							nextLine(const std::string &, size_t &);
	std::string							readKey(const std::string &);
	std::string							readValue(const std::string &);
	// void								setLang();
	void								setBody(const std::string &);
	void								findQuery();
	void								createCgi();
	Request();
	// Request(const Request &);

public:
	Request(const std::string &);
	Request	&operator=(const Request &);
	~Request();
	const std::string							&getMethod() const;
	const std::string							&getVersion() const;
	const std::string							&getUri() const;
	const std::map<std::string, std::string>	&getRequestMap() const;
	const std::string							&getBody() const;
	const std::string							&getQuery() const;
	const std::map<std::string, std::string>	&getEnvForCgi() const;
	int											getRet() const;
	void										setMethod(const std::string);
};


#endif