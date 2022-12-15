/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 12:10:56 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/15 12:10:57 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LOCATION_HPP
# define LOCATION_HPP

# include "webserv.hpp"

class Location
{
private:
	std::string 						_path;
	bool								_autoidx;
	std::map<std::string, std::string>	_locationMap;
public:
	Location();
	~Location();
	std::map<std::string, std::string>	&getLocationMap();
	std::string							&getPath();
	void								setPath(std::string path);
	bool								&getAutoindex();
};


#endif