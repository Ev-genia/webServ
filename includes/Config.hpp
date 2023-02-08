/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Config.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 13:22:52 by wcollen           #+#    #+#             */
/*   Updated: 2023/02/08 15:24:14 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CONFIG_HPP
# define CONFIG_HPP

# include "webserv.hpp"

# define BUFFER_SIZE 2048
# define WORDS_COUNT 12

typedef  std::pair<std::string, std::string> strStrPair;
typedef  std::pair<std::string, bool> strBoolPair;

class Config
{
private:
	std::string			_keyWords[WORDS_COUNT];
	std::string			_contentString;
	std::vector<Server>	_serverTable;
	
	strBoolPair		isKeyWord(std::string src, std::string keyWords[], int num);
	strStrPair		splitConfigParam(std::string src);
	struct s_listen	splitListenParam(std::string src);
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