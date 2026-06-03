/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:11:43 by stephen           #+#    #+#             */
/*   Updated: 2026/06/03 15:13:41 by stephen          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ServerConfig.hpp"

ServerConfig::ServerConfig()
{
	root = "www";
	index = "index.html";

	allowedMethods.push_back("GET");
	allowedMethods.push_back("POST");
	// allowedMethods.push_back("DELETE");
}