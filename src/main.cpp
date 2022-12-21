/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:25:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/21 12:05:58 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int	main(int ac, char **av)
{
	const char  *fileName;

	if (ac > 2)
		exitError("Wrong numbers of arguments");
	if (ac == 1)
		fileName = "config.conf";
	else
		fileName = av[1];

	Config	config(fileName);
	config.parse();
	Handler	handler(config.getConfig());
	handler.initFds();
	handler.serverRun();
}
