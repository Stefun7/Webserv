#include "../includes/ServerConfig.hpp"

ServerConfig::ServerConfig(): _port(0), _server(""), _maxBodySize(0) {}
ServerConfig::ServerConfig(const ServerConfig &copy): _port(copy._port),
_server(copy._server), _errors(copy._errors), _locations(copy._locations),
_maxBodySize(copy._maxBodySize) {
}
ServerConfig &ServerConfig::operator=(const ServerConfig &target){
    if (this != &target){
        _port = target._port;
        _server = target._server;
        _errors = target._errors;
        _locations = target._locations;
        _maxBodySize = target._maxBodySize;
    }
    return *this;
}
ServerConfig::~ServerConfig(){}

int ServerConfig::getPort()const{
    return (_port);
}
std::string ServerConfig::getServer()const{
    return (_server);
}
const std::map<int, std::string>& ServerConfig::getErrors()const{
    return _errors;
}
const std::vector<location> &ServerConfig::getLocations()const{
    return _locations;
}
size_t  ServerConfig::getMaxBodySize()const{
    return _maxBodySize;
}

void    ServerConfig::setPort(int port){
    _port = port;
}
void    ServerConfig::setServer(const std::string &server){
    _server = server;
}
void    ServerConfig::setErrors(int code, const std::string &path){
    _errors[code] = path;
}
void    ServerConfig::setLocations(const location &newLoc){
    _locations.push_back(newLoc);
}
void    ServerConfig::setMaxBodySize(size_t size){
    _maxBodySize = size; // missing a M here no ?
}

const location* findLocation(const std::string& uri, const ServerConfig& config) //new
{
	const std::vector<location>& locs =
		config.getLocations();

	for (size_t i = 0; i < locs.size(); i++)
	{
		if (uri.find(locs[i].getPath()) == 0)
			return &locs[i];
	}
	return NULL;
}

bool methodAllowed(const location& loc, const std::string& method)  //new
{
	const std::vector<std::string>& methods =
		loc.getMethods();

	for (size_t i = 0; i < methods.size(); i++)
	{
		if (methods[i] == method)
			return true;
	}
	return false;
}