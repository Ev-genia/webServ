/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:20 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/20 17:27:16 by mlarra           ###   ########.fr       */
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
	std::string							_path;
	std::map<std::string, std::string>	_requestMap;//need add initRequestMap
	std::string							_body;
	std::map<std::string, std::string>	_envForCgi;
	int									_ret;
	static std::vector<std::string>		availableMethods;
	static std::vector<std::string>		initMethods();
	void								resetRequestMap();
	void								parseRequest(const std::string &);
	void								readFirstLine(const std::string &);
	void								readPath(const std::string &, size_t);
	void								readVersion(const std::string &, size_t);
	void								checkMethod();
	std::string							nextLine(const std::string &, size_t &);
	// std::string							&pop(std::string &);
	void								pop(std::string &);
	std::string							readKey(const std::string &);
	std::string							readValue(const std::string &);
	std::string							&strip(std::string &, char);
	// void								setLang();
	std::vector<std::string>			split(const std::string &, char);
	void								setBody(const std::string &);


public:
	Request(const std::string);
	~Request();
	int									getRet() const;
	void								setMethod(const std::string);
	std::map<std::string, std::string>	&getRequestMap();
};


#endif