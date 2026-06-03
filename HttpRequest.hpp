/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HttpRequest.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/21 13:01:06 by stephen           #+#    #+#             */
/*   Updated: 2026/06/01 01:50:49 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include <iostream>
# include <sstream>
# include <string>
# include <algorithm>
# include <map>
# include <sys/socket.h>

//add some getters to make things pretty
class HttpRequest{
private:
	bool check_empty();
public:
	std::string method;
	std::string uri;
	std::string version;
	std::map<std::string, std::string> headers;
	std::string body;

	bool parse(const std::string& rawRequest);
};

std::string gnl_req(const std::string &rawRequest, size_t &eol);
//classic http request looks like this :
//
//[METHOD] [URI] [VERSION]					//request line
//[HEADERS]
//
//[BODY]