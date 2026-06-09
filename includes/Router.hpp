/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Router.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/31 14:08:55 by stephen           #+#    #+#             */
/*   Updated: 2026/06/09 13:24:14 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
# include "../includes/HttpResponse.hpp"
# include "../includes/HttpRequest.hpp"
# include "../includes/Router.hpp"
# include "../includes/ServerConfig.hpp"
# include <fcntl.h>
# include <unistd.h>

class Router{	//new
private:
public:
	HttpResponse route(const HttpRequest& req, const ServerConfig& config);
};

HttpResponse handleGet(const HttpRequest& request, const ServerConfig& config);
HttpResponse handlePost(const HttpRequest& request, const ServerConfig& config);
HttpResponse handleDelete(const HttpRequest& request, const ServerConfig& config);
HttpResponse errorResponse(int status);