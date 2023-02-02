/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:35:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/02/02 15:26:20 by mlarra           ###   ########.fr       */
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
	if (stat(path.c_str(), &s) == 0 )
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
std::string	getLink(std::string const &dirEntry, std::string const &dirName, std::string const &host, int port)
{
	std::stringstream	ss;

	ss << "\t\t<p><a href=\"http://" + host + ":" << port << dirName + "/" + dirEntry + "\">" + dirEntry + "</a></p>\n";
	return (ss.str());
}

std::string	getPage(const char *enterPath, std::string const &host, int port)
{
	std::string	dirName(enterPath);
	DIR			*dir = opendir(enterPath);
	std::string	page = "<!DOCTYPE html>\n<html>\n<head>\n<title>" + dirName + "</title>\n</head>\n<body>\n<h1>INDEX</h1>\n<p>\n";
	if (dir == NULL)
	{
		std::cerr << "Error: could not open [" << enterPath << "]" << std::endl;
		return "";
	}
	if (dirName[0] != '/')
		dirName = "/" + dirName;
	for (struct dirent *dirEntry = readdir(dir); dirEntry; dirEntry = readdir(dir))
	{
		page += getLink(std::string(dirEntry->d_name), dirName, host, port);
	}
	page += "</p>\n</body>\n</html>\n";
	closedir(dir);
	return (page);
}
