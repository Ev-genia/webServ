#ifndef RESPONSEHEADER_HPP
# define RESPONSSEHEADER_HPP
# include "webserv.hpp"
class ResponseHeader
{
public:
	ResponseHeader();
	~ResponseHeader();

	std::string		notAllowed(std::set<std::string> methods, const std::string& path, int code);
};
#endif