/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:20:34 by stephen           #+#    #+#             */
/*   Updated: 2026/06/03 18:45:45 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Router.hpp"

//A server is just a program that waits for requests and sends responses
//A browser is just a client program that sends HTTP requests.
int main(){
	//check how we recieve the request, need to use recv() and play with byte or something
	// std::string rawRequest =
	// 	"GET /hello.html HTTP/1.1\r\n"
	// 	"Host: localhost:8080\r\n"
	// 	"\r\n";
	// std::string rawRequest =
	// 	"GET /\r\n"
	// 	"\r\n";
	// std::string rawRequest =
	// 	"POST /upload.txt HTTP/1.1\r\n"
	// 	"Content-Length: 11\r\n"
	// 	"\r\n"
	// 	"Hello World\r\n"
	// 	"\r\n";
	// std::string rawRequest =
	// 	"POST /empty.txt HTTP/1.1\r\n"
	// 	"Content-Length: 0\r\n"
	// 	"\r\n";
	// std::string rawRequest =
	// 	"DELETE /upload.txt HTTP/1.1\r\n"
	// 	"\r\n";
	std::string rawRequest =
		"GET / HTTP/1.1\r\n"
		"Host: localhost\r\n"
		"User-Agent: Mozilla/5.0\r\n"
		"Accept: */*\r\n"
		"\r\n";

	HttpRequest request;
	HttpResponse response;

	if (!request.parse(rawRequest))
		response = errorResponse(400);
	else
	{
		Router router;
		response = router.route(request);
	}
	std::cout << response.buildResponse() << std::endl;
	return 0;
}