/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scesar <scesar@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:04:40 by stephen           #+#    #+#             */
/*   Updated: 2026/06/05 16:15:39 by scesar           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <vector>

class ServerConfig{
public:
	ServerConfig();
	std::string root;
	std::string index;
	std::vector<std::string> allowedMethods;
};

// socket() : Creates a socket (endpoint)
// bind() : Assigns an address and port to the socket
// listen() : Turns the socket into a server
// accept() : Accepts one incoming connection
// recv() : Receives bytes from the client
// send() : Sends bytes back
