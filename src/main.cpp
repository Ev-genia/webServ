/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/30 12:25:05 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/06 14:50:18 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/webserv.hpp"

int	main(int argc, char **argv)
{
	if (argc != 2)
		exitError("Bad arguments");
	Config config(argv[1]);
}
