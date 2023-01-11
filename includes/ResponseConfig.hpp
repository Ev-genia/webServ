#ifndef REPONSECONFIG_HPP
# define RESPONSECONFIG_HPP

# include "webserv.hpp"

class ResponseConfig
{
private:
	std::string		_contentLocation;
	std::string		_path;
	std::string		_error_page;// ????
	unsigned long	body_size; // max size for the client body, defaults to 8 000??
	std::string		_lang;

	std::vector<std::string>			_extension_cgi;
	std::string							_exec_cgi;

public:
	ResponseConfig(Config &config, Request &request);
	~ResponseConfig();

	std::vector<std::string>	makeCgiVector();
};




# endif