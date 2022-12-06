/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:25:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/05 16:38:20 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int	main(int ac, char **av)
{
	if (ac != 2)
		exitError("Wrong numbers of arguments");
	Config	configuratoin(av[1]);
	Handler	handler(configuratoin.getConfig());
	handler.initFds();
	handler.serverRun();
}
