/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:52 by wcollen           #+#    #+#             */
/*   Updated: 2022/12/14 17:32:41 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 1024

class Config
{
private:
	std::string _keyWords[11];
	std::string	_contentString;
	std::vector<Server> _serverTable;
	
	std::pair<std::string, bool>		isKeyWord(std::string src, std::string keyWords[], int num);
	std::pair<std::string, std::string> splitConfigParam(std::string src);
	void								trimConfigStr(std::string &str);
	std::string							extractPathFromStrConfig(std::string src, int pos);
	void								parseServerConfig(bool &inServer, bool &inLocation, int &pos, int &serverCount);
	void								parseLocationConfig(bool &inLocation, int &pos, int &servCount, std::pair<std::string, bool> &wordInConfig);
public:
	Config(const char *fileName);
	~Config();

	void					parse();
	
	void					check();
	std::vector	<Server>	*getConfig();
	
};

#endif