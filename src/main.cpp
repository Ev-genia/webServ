/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:50:04 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/05 10:56:01 by wcollen          ###   ########.fr       */
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