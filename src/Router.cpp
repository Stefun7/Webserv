/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 14:08:18 by stephen           #+#    #+#             */
/*   Updated: 2026/06/09 13:49:40 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../includes/Router.hpp"
# include "../includes/cgi.hpp"

HttpResponse Router::route(const HttpRequest& request, const ServerConfig& config){
	if (request.getMethod() == "GET")
		return handleGet(request, config);

	if (request.getMethod() == "POST")
		return handlePost(request, config);

	if (request.getMethod() == "DELETE") //how can we delete file without unlink or delete ?
		return handleDelete(request, config);

	return errorResponse(400);
}

HttpResponse handleGet(const HttpRequest& request, const ServerConfig& config){
	HttpResponse response;

	const location* loc = findLocation(request.getUri(), config);	//new
	if (!loc)
		return errorResponse(404);
	if (!methodAllowed(*loc, request.getMethod()))
		return errorResponse(405);

	std::string path;		//new (appens actual path)
	path = loc->getRoot();
	if(request.getUri() == "/")
		path += "/" + loc->getIndex();
	else
		path += "/" + request.getUri();
	std::cout << "PATH = [" << path << "]" << std::endl;
	if (path.find(".py") != std::string::npos) {
        CgiHandler cgi;
        response.body = cgi.executeCGI(path);
        response.statusCode = 200;
        // Si votre script Python renvoie déjà "Content-type: text/html\n\n",
        // ca s'ajoutera au corps . classique en CGI basique.
        return response;
}
		int fd = open(path.c_str(), O_RDONLY);
	if (fd < 0)
		return errorResponse(404);
	response.statusCode = 200;
	response.headers["Content-Type"] = "text/html";
	char buffer[1024];
	ssize_t bytes;

	while ((bytes = read(fd, buffer, sizeof(buffer))) > 0)
		response.body.append(buffer, bytes);

	close(fd);
	std::cout << "Server name: " << config.getServer() << std::endl;

	return response;
}

HttpResponse handlePost(const HttpRequest& request, const ServerConfig& config){
	HttpResponse response;

	const location* loc = findLocation(request.getUri(), config);	//new
	if (!loc)
		return errorResponse(404);
	if (!methodAllowed(*loc, request.getMethod()))
		return errorResponse(405);

	std::string path;		//new (appens actual path)
	path = loc->getRoot();
	if(request.getUri() == "/")
		path += loc->getIndex();
	else
		path += request.getUri();
	if (path.find(".py") != std::string::npos) {
        CgiHandler cgi;
        response.body = cgi.executeCGI(path);
        response.statusCode = 200;
        return response;
	}
	int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);	//0644 here is in octal and means rw-r--r-- (owner : 6 = 4 + 2 = r&w | group : 4 = r | others : 4 = r)
	if(fd < 0)
		return errorResponse(404);
	write(fd, request.getBody().c_str(), request.getBody().size()); //might need to check write
	close(fd);

	response.statusCode = 201;
	response.headers["Content-Type"] = "text/html";
	response.body = "<h1>File Created</h1>";

	return response;
}

HttpResponse handleDelete(const HttpRequest& request, const ServerConfig& config){
	HttpResponse response;

	const location* loc = findLocation(request.getUri(), config);	//new
	if (!loc)
		return errorResponse(404);
	if (!methodAllowed(*loc, request.getMethod()))
		return errorResponse(405);

	std::string path;		//new (appens actual path)
	path = loc->getRoot();
	if(request.getUri() == "/")
		path += loc->getIndex();
	else
		path += request.getUri();

	if (access(path.c_str(), F_OK) != 0)
		return errorResponse(404);
	if (std::remove(path.c_str()) != 0)
	{
		response.statusCode = 500;
		response.headers["Content-Type"] = "text/html";
		response.body = "<h1>500 Internal Server Error</h1>";
		return response;
	}
	response.statusCode = 200;
	response.headers["Content-Type"] = "text/html";
	response.body = "<h1>File Deleted</h1>";

	return response;
}

HttpResponse errorResponse(int status){
	HttpResponse response;

	response.statusCode = status;
	response.headers["Content-Type"] = "text/html";
	response.body = "<h1>404 Not Found</h1>";
	return response;
}