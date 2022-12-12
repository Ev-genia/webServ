/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:56:20 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/12 17:16:34 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
# define REQUEST_HPP

# include "webserv.hpp"

class Request
{
private:
	int			_ret;
	std::string	_metod;
public:
	Request(const std::string);
	~Request();
	int		getRet() const;
	void	setMethod(const std::string);
};


#endif