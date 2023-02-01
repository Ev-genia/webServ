/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/01 16:28:04 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/utils.hpp"

void	exitError(std::string str)
{
	perror(str.c_str());
	// std::cerr << " error exit" << std::endl;
	exit(1);
}

std::string	&strip(std::string &str, char c)
{
	size_t	i;

	if (!str.size())
		return (str);
	i = str.size();
	while (i && str[i - 1] == c)
		i--;
	str.resize(i);
	for (i = 0; str[i] == c; i++);
	str = str.substr(i, std::string::npos);
	return (str);
}

void	pop(std::string &str)
{
	if (str.size())
		str.resize(str.size() - 1);
}

std::vector<std::string>	split(const std::string &str, char c)
{
	std::vector<std::string>	tokens;
	std::istringstream			tokenStream(str);
	std::string					token;

	while (std::getline(tokenStream, token, c))
		tokens.push_back(token);
	return (tokens);
}

std::string	to_string(size_t enter)
{
	std::stringstream	str;

	str << enter;
	return (str.str());
}

int		pathIsFile(const std::string& path)
{
	struct stat s;
	if (stat(path.c_str(), &s) == 0 )
	{
		if (s.st_mode & S_IFDIR)
			return 0;
		else if (s.st_mode & S_IFREG)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}