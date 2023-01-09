/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:08 by mlarra            #+#    #+#             */
/*   Updated: 2022/12/30 13:14:29 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "webserv.hpp"

void						exitError(std::string str);
std::string					&strip(std::string &, char);
void						pop(std::string &);
std::vector<std::string>	split(const std::string &, char);
std::string					to_string(size_t enter);

#endif
