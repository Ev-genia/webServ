/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:23:51 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/06 13:08:29 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include "webserv.hpp"

class Server;

class Handler
{
private:
	std::vector<Server>	*_serverVector;
public:
	Handler(std::vector<Server> *);
	~Handler();
	void	serverRun();
};


#endif