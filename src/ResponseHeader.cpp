#include "../includes/ResponseHeader.hpp"

ResponseHeader::ResponseHeader()
{
	resetValues();
}

ResponseHeader::~ResponseHeader(){}

//responseConf.getAllowedMethods(), responseConf.getContentLocation(), _code
std::string	ResponseHeader::notAllowed(std::set<std::string> methods, const std::string& path, int code)
{
	std::string header;

	resetValues();
	setValues(0, path, code, "", path);
	//setAllow(methods);

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

	setContentLength(size);
	setContentLocation(contentLocation, code);
	setContentType(type, path);
	setDate();
	setLastModified(path);
	setLocation(code, path);
	setRetryAfter(code, 3);
	setServer();
	setTransferEncoding();
	setWwwAuthenticate(code);
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