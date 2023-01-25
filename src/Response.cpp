/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Response.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlarra <mlarra@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 15:26:03 by mlarra            #+#    #+#             */
/*   Updated: 2023/01/25 15:17:34 by mlarra           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Response.hpp"

Response::Response(strStrMap requestMap, Server &server, Client *client)
	:_requestMap(requestMap), _server(server), _client(client){}

Response::~Response(){}

