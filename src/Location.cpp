/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:11:17 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/20 11:08:02 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Location.hpp"

Location::Location(): _path(), _autoidx(false), _locationMap(){}

Location::~Location(){};

strStrMap &Location::getLocationMap()
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

void		Location::setAutoindex(bool index)
{
	this->_autoidx = index;
}

bool	&Location::getAutoindex()
{
	return this->_autoidx;
}

