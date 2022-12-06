#ifndef LOCATION_HPP
# define LOCATION_HPP
# include <iostream>
# include <map>

class Location
{
private:
	std::string 						_path;
	bool								_autoidx;
	std::map<std::string, std::string>	_locations;
public:
	Location();
	~Location();
	std::map<std::string, std::string>	&getLocations();
	std::string							&getPath();
	void								setPath(std::string path);
	bool								&getAutoindex();
};


#endif