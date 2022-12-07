/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/07 17:01:44 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

void	exitError(std::string str)
{
	perror(str.c_str());
	// std::cerr << " error exit" << std::endl;
	exit(1);
}
