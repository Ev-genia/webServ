/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:52 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/05 13:22:57 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define IFNDEF_HPP
# include <iostream>
# include <vector>
# include <fcntl.h>
# include <unistd.h>
# include <iostream>

# include "Server.hpp"

# define BUFFER_SIZE 1024

class Config
{
private:
	std::string _keyWords[11];
	std::string	_contentString;
	std::vector<Server> _serverTable;
public:
	Config(const char *fileName);
	~Config();

	void					parse();
	void					check();
	std::vector	<Server>	*getConfig(); 	
};

#endif