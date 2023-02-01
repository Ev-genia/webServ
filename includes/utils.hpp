/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:08 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 16:27:27 by wcollen          ###   ########.fr       */
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
int							pathIsFile(const std::string& path);

#endif
