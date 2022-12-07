#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "webserv.hpp"

class Location
{
private:
	std::string 						_path;
	bool								_autoidx;
	std::map<std::string, std::string>	_locationStrMap;
public:
	Location();
	~Location();
	std::map<std::string, std::string>	&getLocationStrMap();
	std::string							&getPath();
	void								setPath(std::string path);
	bool								&getAutoindex();
};


#endif