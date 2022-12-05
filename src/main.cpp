/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:25:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/02 10:55:09 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

void	exitError(std::string str)
{
	std::cerr << str << std::endl;
	exit(1);
}

int	main(int argc, char **argv)
{
	if (argc != 2)
		exitError("Bad arguments");
}
