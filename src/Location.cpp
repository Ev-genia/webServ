#include "Location.hpp"

Location::Location(): _path(), _autoidx(false), _locations(){}

Location::~Location(){};

std::map<std::string, std::string> &Location::getLocations()
{
	return this->_locations;
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

