/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:20 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/15 17:36:06 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "webserv.hpp"



class Request
{
private:
	int									_ret;
	std::string							_metod;//TO DO: заменить на вставку строки в _requestMap
	std::map<std::string, std::string>	_requestMap;
	void								parseRequest(const std::string &);
	void								readFirstLine(const std::string &);
	std::string							nextLine(const std::string &, size_t &);
	// std::string							&pop(std::string &);
	void								pop(std::string &);
public:
	Request(const std::string);
	~Request();
	int									getRet() const;
	void								setMethod(const std::string);
	// std::map<std::string, std::string>	&getRequestMap();
};


#endif