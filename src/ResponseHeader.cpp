#include "../includes/ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
	resetValues();
}

std::string		ResponseHeader::getHeader(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation)
{
	std::string	header;

	resetValues();
	setValues(size, path, code, type, contentLocation);

	header = "HTTP/1.1 " + to_string(code) + " " + getStatusMessage(code) + "\r\n";
std::cout << "ResponseHeader::ResponseHeader()| header1:" << header << std::endl;
	header += writeHeader();
std::cout << "ResponseHeader::ResponseHeader()| heder2" << header  << std::endl;
std::cout << "ResponseHeader::ResponseHeader()| end func" << std::endl;
	return (header);
}

void			ResponseHeader::initErrorMap()
{
	_errors[100] = "Continue";
	_errors[200] = "OK";
	_errors[201] = "Created";
	_errors[204] = "No Content";
	_errors[400] = "Bad Request";
	_errors[403] = "Forbidden";
	_errors[404] = "Not Found";
	_errors[405] = "Method Not Allowed";
	_errors[413] = "Payload Too Large";
	_errors[500] = "Internal Server Error";
	_errors[501] = "The HTTP Not Implemented";
}

std::string		ResponseHeader::writeHeader(void)
{
	std::string	header = "";

	if (_allow != "")
		header += "Allow: " + _allow + "\r\n";
	if (_contentLanguage != "")
		header += "Content-Language: " + _contentLanguage + "\r\n";
	if (_contentLength != "")
		header += "Content-Length: " + _contentLength + "\r\n";
	if (_contentLocation != "")
		header += "Content-Location: " + _contentLocation + "\r\n";
	if (_contentType != "")
		header += "Content-Type: " + _contentType + "\r\n";
	if (_date != "")
		header += "Date: " + _date + "\r\n";
	if (_lastModified != "")
		header += "Last-Modified: " + _lastModified + "\r\n";
	if (_location != "")
		header += "Location: " + _location + "\r\n";
	if (_retryAfter != "")
		header += "Retry-After: " + _retryAfter + "\r\n";
	if (_server != "")
		header += "Server: " + _server + "\r\n";
	if (_transferEncoding != "")
		header += "Transfer-Encoding: " + _transferEncoding + "\r\n";
	if (_wwwAuthenticate != "")
		header += "WWW-Authenticate: " + _wwwAuthenticate + "\r\n";
std::cout << "ResponseHeader::writeHeader| end func" << std::endl;
std::cout << "ResponseHeader::writeHeader| header: " << header << std::endl;
	return (header);
}

std::string		ResponseHeader::getStatusMessage(int code)
{
	if (_errors.find(code) != _errors.end())
		return _errors[code];
	return ("Unknown Code");
}

ResponseHeader::~ResponseHeader(){}

std::string	ResponseHeader::notAllowed(std::set<std::string> methods, const std::string& path, int code)
{
	std::string header;

	resetValues();
	setValues(0, path, code, "", path);
	setAllow(methods);

	if (code == 405)
		header = "HTTP/1.1 405 Method Not Allowed\r\n";
	else if (code == 413)
		header = "HTTP/1.1 413 Payload Too Large\r\n";
	header += writeHeader();

	return (header);
}


void			ResponseHeader::setValues(size_t size, const std::string& path, int code, std::string type, const std::string& contentLocation)
{
	setAllow();

	_contentLength = to_string(size);
	_contentLocation = contentLocation;
	setContentType(type, path);
	setDate();
	setLastModified(path);
	setLocation(code, path);
	setRetryAfter(code, 3);
	_server = "chicki-ricki webserv/1.0.0 (Unix)";
	_transferEncoding = "identity";
	setWwwAuthenticate(code);
std::cout << "ResponseHeader::setValues| end func" << std::endl;
}

void			ResponseHeader::resetValues(void)
{
	_allow = "";

	_contentLength = "";
	_contentLocation = "";
	_contentType = "";
	_date = "";
	_lastModified = "";
	_location = "";
	_retryAfter = "";
	_server = "";
	_transferEncoding = "";
	_wwwAuthenticate = "";
	
	initErrorMap();
}

void			ResponseHeader::setAllow(std::set<std::string> methods)
{
	std::set<std::string>::iterator it = methods.begin();

	while (it != methods.end())
	{
		_allow += *(it++);

		if (it != methods.end())
			_allow += ", ";
	}
}

void			ResponseHeader::setAllow(const std::string& allow)
{
	_allow = allow;
}

void			ResponseHeader::setContentType(std::string type, std::string path)
{
	if (type != "")
	{
		_contentType = type;
		return ;
	}
	type = path.substr(path.rfind(".") + 1, path.size() - path.rfind("."));
std::cout << "ResponseHeader::setContentType| type: " << type << std::endl;

	if (type == "html")
		_contentType = "text/html";
	else if (type == "css")
		_contentType = "text/css";
	else if (type == "js")
		_contentType = "text/javascript";
	else if (type == "jpeg" || type == "jpg")
		_contentType = "image/jpeg";
	else if (type == "png")
		_contentType = "image/png";
	else if (type == "bmp")
		_contentType = "image/bmp";
	else
		_contentType = "text/plain";
std::cout << "ResponseHeader::setContentType| end func "<< std::endl;
}

void			ResponseHeader::setDate(void)
{
	char			buffer[100];
	struct timeval	tv;
	struct tm		*tm;

	gettimeofday(&tv, NULL);
	tm = gmtime(&tv.tv_sec);
	strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
	_date = std::string(buffer);
}

void			ResponseHeader::setLastModified(const std::string& path)
{
	char			buffer[100];
	struct stat		stats;
	struct tm		*tm;

	if (stat(path.c_str(), &stats) == 0)
	{
		tm = gmtime(&stats.st_mtime);
		strftime(buffer, 100, "%a, %d %b %Y %H:%M:%S GMT", tm);
		_lastModified = std::string(buffer);
	}
}

void			ResponseHeader::setLocation(int code, const std::string& redirect)
{
	if (code == 201 || code / 100 == 3)
	{
		_location = redirect;
	}
}

void			ResponseHeader::setRetryAfter(int code, int sec)
{
	if (code == 503 || code == 429 || code == 301)
	{
		_retryAfter = to_string(sec);
	}
}

void			ResponseHeader::setWwwAuthenticate(int code)
{
	if (code == 401)
	{
		_wwwAuthenticate = "Basic realm=\"Sorry, authentication failed😢\" charset=\"UTF-8\"";
	}
}