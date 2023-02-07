/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/07 14:05:39 by mlarra           ###   ########.fr       */
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

int	pathIsFile(const std::string& path)
{
	struct stat	s;
	if (stat(path.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
			return (0);
		else if (s.st_mode & S_IFREG)
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

int	pathIsDir(const std::string& path)
{
	struct stat	s;
	if (stat(path.c_str(), &s) == 0)
	{
		if (s.st_mode & S_IFDIR)
			return (1);
	}
	return (0);
}

std::string	getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port, Request &request)
{
	std::stringstream	ss;

	ss << "\t\t<p><a href=\"." + host + ":" << port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
	return (ss.str());
}

std::string	getPage(const char *enterPath, std::string const &host, int port, Request &request)
{
	std::string		dirName(enterPath);
	DIR				*dir = opendir(enterPath);
	struct dirent	*dirEntry;
	std::string	page = "<!DOCTYPE html>\n<html>\n<head>\n<title>" + dirName + "</title>\n</head>\n<body>\n<h2>AUTOINDEX ON</h2>\n<p>\n";

	dirEntry = readdir(dir);
	


	while ((dirEntry = readdir(dir)) != NULL)
	{
		if (dirEntry->d_name[0] == '.')
			continue;
		if (request.getUri()[request.getUri().length() - 1] != '/')
			page += "\t\t<p><a href=\"." + request.getUri() + "/" + dirEntry->d_name + "\">" + dirEntry->d_name + "</a></p>\n";
		else
			page += "\t\t<p><a href=\"." + request.getUri() + /*"/" + */dirEntry->d_name + "\">" + dirEntry->d_name + "</a></p>\n";
	}
	closedir(dir);
	page += "</p>\n</body>\n</html>\n";
	return (page);
}

int	checkEnd(const std::string& str, const std::string& end)
{
	size_t	i = str.size();
	size_t	j = end.size();

	while (j > 0)
	{
		i--;
		j--;
		if (i < 0 || str[i] != end[j])
			return (1);
	}
	return (0);
}
