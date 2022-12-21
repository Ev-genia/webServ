/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:08 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/21 11:09:45 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "webserv.hpp"

void						exitError(std::string str);
std::string					&strip(std::string &, char);
void						pop(std::string &);
std::vector<std::string>	split(const std::string &, char);


#endif
