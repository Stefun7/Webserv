/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/05 16:19:39 by scesar            #+#    #+#             */
/*   Updated: 2026/06/05 16:46:10 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "HttpRequest.hpp"
#include "HttpResponse.hpp"
#include "Router.hpp"

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

//A server is just a program that waits for requests and sends responses
//A browser is just a client program that sends HTTP requests.
int main()
{
	int server_fd = socket(AF_INET, SOCK_STREAM, 0);

	sockaddr_in addr;
	std::memset(&addr, 0, sizeof(addr));

	addr.sin_family = AF_INET;
	addr.sin_port = htons(8080);
	addr.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(server_fd, (sockaddr*)&addr, sizeof(addr));

	listen(server_fd, 10);

	std::cout << "Listening on port 8080..." << std::endl;
	Router router;
	while (true)
	{
		int client_fd = accept(server_fd, NULL, NULL);
		// std::cout << "ACCEPTED CLIENT" << std::endl;
		if (client_fd < 0)
			continue;

		char buffer[4096];
		ssize_t bytes = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
		// std::cout << "RECV CALLED" << std::endl;
		// std::cout << "BYTES = " << bytes << std::endl;

		if (bytes <= 0)
		{
			close(client_fd);
			continue;
		}

		buffer[bytes] = '\0';

		HttpRequest req;
		HttpResponse response;

		if (!req.parse(buffer))
			response = errorResponse(400);
		else
			response = router.route(req);

		std::string res_str = response.buildResponse();

		// std::cout << "BEFORE SEND" << std::endl;
		send(client_fd, res_str.c_str(), res_str.size(), 0);
		std::cout << res_str << std::endl;

		close(client_fd);
	}

	close(server_fd);
}

// int main(){
// 	check how we recieve the request, need to use recv() and play with byte or something
// 	std::string rawRequest =
// 		"GET /hello.html HTTP/1.1\r\n"
// 		"Host: localhost:8080\r\n"
// 		"\r\n";
// 	std::string rawRequest =
// 		"GET /\r\n"
// 		"\r\n";
// 	std::string rawRequest =
// 		"POST /upload.txt HTTP/1.1\r\n"
// 		"Content-Length: 11\r\n"
// 		"\r\n"
// 		"Hello World\r\n"
// 		"\r\n";
// 	std::string rawRequest =
// 		"POST /empty.txt HTTP/1.1\r\n"
// 		"Content-Length: 0\r\n"
// 		"\r\n";
// 	std::string rawRequest =
// 		"DELETE /upload.txt HTTP/1.1\r\n"
// 		"\r\n";
// 	std::string rawRequest =
// 		"GET / HTTP/1.1\r\n"
// 		"Host: localhost\r\n"
// 		"User-Agent: Mozilla/5.0\r\n"
// 		"Accept: */*\r\n"
// 		"\r\n";

// 	HttpRequest request;
// 	HttpResponse response;

// 	if (!request.parse(rawRequest))
// 		response = errorResponse(400);
// 	else
// 	{
// 		Router router;
// 		response = router.route(request);
// 	}
// 	std::cout << response.buildResponse() << std::endl;
// 	return 0;
// }
