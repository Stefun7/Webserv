/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerConfig.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stephen <stephen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/03 15:04:40 by stephen           #+#    #+#             */
/*   Updated: 2026/06/03 15:14:31 by stephen          ###   ########.fr       */
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