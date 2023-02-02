/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:11:54 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/02 16:35:47 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP
# include "webserv.hpp"
class ResponseHeader
{
private:
	std::string					_allow;
	std::string					_contentLanguage;
	std::string					_contentLength;
	std::string					_contentLocation;
	std::string					_contentType;
	std::string					_date;
	std::string					_lastModified;
	std::string					_location;
	std::string					_retryAfter;
	std::string					_server;
	std::string					_transferEncoding;
	std::string					_wwwAuthenticate;
	std::map<int, std::string>	_errors;

	void						initErrorMap();
public:
	ResponseHeader();
	~ResponseHeader();

	void			setAllow(std::set<std::string> methods);

	void			setAllow(const std::string& allow = "");
	void			setContentType(std::string type, std::string path);
	void			setDate(void);
	void			setLastModified(const std::string& path);
	void			setLocation(int code, const std::string& redirect);
	void			setRetryAfter(int code, int sec);
	void			setWwwAuthenticate(int code);
	
	std::string		getHeader(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation);
	std::string		getStatusMessage(int code);

	std::string		writeHeader(void);
	void			setValues(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation);
	void			resetValues(void);
	std::string		notAllowed(std::set<std::string> methods, const std::string& path, int code);
};
#endif
