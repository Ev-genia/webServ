/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:02 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/12 17:16:38 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

Request::Request(const std::string str): _ret(200)
{
	if (_ret != 200)
		std::cerr << "Error init request" << std::endl;
}

Request::~Request()
{
}

int	Request::getRet() const
{
	return (_ret);
}

void	Request::setMethod(const std::string enterMetod)
{
	_metod = enterMetod;
}
