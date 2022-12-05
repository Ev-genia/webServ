/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Handler.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 15:23:51 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/05 15:45:16 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HANDLER_HPP
# define HANDLER_HPP

# include "webserv.hpp"

class Server;

class Handler
{
private:
	std::vector<Server>	*_servers;
public:
	Handler(std::vector<Server> *);
	~Handler();
	void	serverRun();
};


#endif