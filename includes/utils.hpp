/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:08 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/02 15:11:03 by mlarra           ###   ########.fr       */
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
// static std::string			getPage(const char *, std::string const &, int);
std::string					getPage(const char *, std::string const &, int);
std::string					getLink(std::string const &, std::string const &, std::string const &, int );

#endif
