/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CgiHandler.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:26:02 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/27 22:23:07 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CgiHandler.hpp"

CgiHandler::CgiHandler(Request &request, ResponseConfig &respConfig): _body(request.getBody())
{
	initEnv(request, respConfig);
}
CgiHandler::~CgiHandler()
{
	return ;
}

void	CgiHandler::initEnv(Request &request, ResponseConfig &respConf)
{
	std::map<std::string, std::string>	headers;

	headers = request.getRequestMap();
	if (headers.find("Auth-Scheme") != headers.end() && headers["Auth-Scheme"] != "")
		_env["AUTH_TYPE"] = headers["Auth-Scheme"];
	_env["REDIRECT_STATUS"] = "200";
	_env["GATEWAY_INTERFACE"] = "CGI/1.1";
	_env["SCRIPT_NAME"] = respConf.getPath();
	_env["SCRIPT_FILENAME"] = respConf.getPath();
	_env["REQUEST_METHOD"] = request.getMethod();
	_env["CONTENT_LENGHT"] = std::to_string(_body.length());
	_env["CONTENT_TYPE"] = headers["Content-type"];
	_env["PATH_INFO"] = request.getUri();
	_env["PATH_TRANSLATED"] = request.getUri();
	_env["QUERY_STRING"] = request.getQuery();
	_env["REMOTEaddr"] = to_string(respConf.getServer().getListen().host);//Удаленный IP-адрес, с которого пользователь делает запрос.
	// _env["REMOTE_IDENT"] = headers["Authorization"];
	// _env["REMOTE_USER"] = headers["Authorization"];
	_env["REQUEST_URI"] = request.getUri() + request.getQuery();
	if (headers.find("Hostname") != headers.end())
		_env["SERVER_NAME"] = headers["Hostname"];
	else
		_env["SERVER_NAME"] = _env["REMOTEaddr"];
	_env["SERVER_PORT"] = respConf.getServer().getListen().port;
	_env["SERVER_PROTOCOL"] = "HTTP/1.1";
	_env["SERVER_SOFTWARE"] = "Webserv/1.0";
	// _env.insert();
}

char	**CgiHandler::convertEnvToCStrArr() const
{
	char	**env;
	int		j;

	env = new char*[_env.size() + 1];
	j = 0;
	for (std::map<std::string, std::string>::const_iterator it = _env.begin(); it != _env.end(); it++)
	{
		std::string	elem = it->first + "=" + it->second;
		env[j] = new char[elem.size() + 1];
		env[j] = strcpy(env[j], (const char *)elem.c_str());
		j++;
	}
	return (env);
}

std::string	CgiHandler::executeCgi(const std::string &nameScript)
{
	char		**env;
	int			saveStdIn;
	int			saveStdOut;
	pid_t		pid;
	std::string	bodyReturn;

	try
	{
		env = convertEnvToCStrArr();
	}
	catch(const std::bad_alloc& e)
	{
		std::cerr << e.what() << '\n';
	}
	saveStdIn = dup(STDIN_FILENO);
	saveStdOut = dup(STDOUT_FILENO);
	FILE	*fileIn = tmpfile();
	FILE	*fileOut = tmpfile();
	int		fdIn = fileno(fileIn);
	int		fdOut = fileno(fileOut);
	int		ret = 1;
	write(fdIn, _body.c_str(), _body.size());
	lseek(fdIn, 0, SEEK_SET);
	pid = fork();
	if (pid == -1)
	{
		std::cerr << "Fork error" << std::endl;
		return ("Status: 500\r\n\r\n");
	}
	else if (pid == 0)
	{
		// это указатель, элементы char которого не могут быть изменены, но сам указатель может
		char * const	*nll;

		nll = NULL;
		dup2(fdIn, STDIN_FILENO);
		dup2(fdOut, STDOUT_FILENO);
		execve(nameScript.c_str(), nll, env);
		std::cerr << "Execve error" << std::endl;
		write(STDOUT_FILENO, "Status: 500\r\n\r\n", 15);
	}
	else
	{
		char	buff[CGI_BUFF_SIZE];// = {0};

		waitpid(-1, NULL, 0);
		lseek(fdOut, 0, SEEK_SET);
		ret = 1;
		while (ret > 0)
		{
			memset(buff, 0, CGI_BUFF_SIZE);
			ret = read(fdOut, buff, CGI_BUFF_SIZE - 1);
			bodyReturn += buff;
		}
	}
	dup2(saveStdIn, STDIN_FILENO);
	dup2(saveStdOut, STDOUT_FILENO);
	fclose(fileIn);
	fclose(fileOut);
	close(fdIn);
	close(fdOut);
	close(saveStdIn);
	close(saveStdOut);
	for (int i = 0; env[i]; i++)
		delete[] env[i];
	delete[] env;
	if (pid == 0)
		exit(0);
	return (bodyReturn);
}
