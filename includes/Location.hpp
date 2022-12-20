/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:10:56 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/20 11:33:32 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "webserv.hpp"

typedef  std::map<std::string, std::string> strStrMap;

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
	bool		&getAutoindex();
	void		setPath(std::string path);
	void		setAutoindex(bool index);
};


#endif