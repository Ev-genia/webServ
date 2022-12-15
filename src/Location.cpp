#include "../includes/Location.hpp"

Location::Location(): _path(), _autoidx(false), _locationMap(){}

Location::~Location(){};

std::map<std::string, std::string> &Location::getLocationMap()
{
	return this->_locationMap;
}

std::string &Location::getPath()
{
	return this->_path;
}

void		Location::setPath(std::string path)
{
	this->_path = path;
}

bool	&Location::getAutoindex()
{
	return this->_autoidx;
}

