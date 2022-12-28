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
public:
	ResponseConfig(Config &config, Request &request);
	~ResponseConfig();
};




# endif