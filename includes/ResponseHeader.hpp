/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ResponseHeader.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/02 12:11:54 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/02 12:12:18 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONSEHEADER_HPP
# define RESPONSEHEADER_HPP
# include "webserv.hpp"
class ResponseHeader
{
public:
	ResponseHeader();
	~ResponseHeader();

	std::string		notAllowed(std::set<std::string> methods, const std::string& path, int code);
};
#endif