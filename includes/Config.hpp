/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wcollen <wcollen@student.21-school.ru>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:52 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/15 23:05:13 by wcollen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 1024
# define strBoolPair std::pair<std::string, bool>
# define strStrPair std::pair<std::string, std::string>
class Config
{
private:
	std::string			_keyWords[11];
	std::string			_contentString;
	std::vector<Server>	_serverTable;
	
	strBoolPair		isKeyWord(std::string src, std::string keyWords[], int num);
	strStrPair 		splitConfigParam(std::string src);
	void			trimConfigStr(std::string &str);
	std::string		extractPathFromStrConfig(std::string src, int pos);
	void			parseServerConfig(bool &inServer, bool &inLocation, int &pos, int &serverCount);
	void			parseLocationConfig(bool &inLocation, int &pos, int &servCount, strBoolPair &wordInConfig);
public:
	Config(const char *fileName);
	~Config();

	void					parse();
	
	void					check();
	std::vector	<Server>	*getConfig();
	
};

#endif