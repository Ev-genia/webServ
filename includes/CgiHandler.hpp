/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:25:58 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/23 23:27:47 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CGIHANDLER_HPP
# define CGIHANDLER_HPP

# include "webserv.hpp"

class CgiHandler
{
private:
	std::map<std::string, std::string>	_env;
	std::string							_body;
	void								initEnv(Request &);
public:
	CgiHandler(Request &);
};

#endif