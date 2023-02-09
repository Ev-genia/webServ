/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:08 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/09 11:16:37 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include "webserv.hpp"

class Request;

void						exitError(std::string str);
std::string					&strip(std::string &, char);
void						pop(std::string &);
std::vector<std::string>	split(const std::string &, char);
std::string					to_string(size_t enter);
int							pathIsFile(const std::string& path);
int							pathIsDir(const std::string& path);
std::string					getPage(const char *, Request &);
// std::string					getLink(std::string const &, std::string const &, std::string const &, int);
int							checkEnd(const std::string& str, const std::string& end);

#endif
