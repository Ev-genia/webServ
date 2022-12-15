/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:10:56 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/15 23:06:06 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "webserv.hpp"

# define strStrMap std::map<std::string, std::string>

class Location
{
private:
	std::string 		_path;
	bool				_autoidx;
	strStrMap			_locationMap;
public:
	Location();
	~Location();
	strStrMap	&getLocationMap();
	std::string	&getPath();
	void		setPath(std::string path);
	bool		&getAutoindex();
};


#endif