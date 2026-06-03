/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 14:08:18 by stephen           #+#    #+#             */
/*   Updated: 2026/06/03 16:36:32 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Router.hpp"

HttpResponse Router::route(const HttpRequest& request)	//new
{
	if (request.method == "GET")
		return handleGet(request);

	if (request.method == "POST")
		return handlePost(request);

	if (request.method == "DELETE") //how can we delete file without unlink or delete ?
		return handleDelete(request);

	return errorResponse(400);
}

HttpResponse handleGet(const HttpRequest& request)	//new
{
	HttpResponse response;

	std::string path;

	if(request.uri == "/")
		path = "www/index.html";	//default page
	else
		path = "www" + request.uri;		//will need to update bc uri not always = path
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

	return response;
}

HttpResponse handlePost(const HttpRequest& request){	//new
	HttpResponse response;

	std::string path;
	if(request.uri == "/")
		path = "www/index.html";	//default page
	else
		path = "www" + request.uri;
	int fd = open(path.c_str(), O_CREAT | O_WRONLY | O_TRUNC, 0644);	//0644 here is in octal and means rw-r--r-- (owner : 6 = 4 + 2 = r&w | group : 4 = r | others : 4 = r)
	if(fd < 0)
		return errorResponse(404);
	write(fd, request.body.c_str(), request.body.size()); //might need to check write
	close(fd);

	response.statusCode = 201;
	response.headers["Content-Type"] = "text/html";
	response.body = "<h1>File Created</h1>";

	return response;
}

HttpResponse handleDelete(const HttpRequest& request)	//new
{
	HttpResponse response;

	std::string path;

	if (request.uri == "/")
		path = "www/index.html";
	else
		path = "www" + request.uri;

	if (access(path.c_str(), F_OK) != 0)
		return errorResponse(404);
	if (unlink(path.c_str()) != 0)	//unlink not in allowed function but don't know how to delete then...?
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
HttpResponse errorResponse(int status){	//new
	HttpResponse response;

	response.statusCode = status;
	response.headers["Content-Type"] = "text/html";
	response.body = "<h1>404 Not Found</h1>";
	return response;
}