/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_new.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:01:31 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/28 22:21:38 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//----------------------------------------------------------------------------->
//	AGGIORNARE DOCUMENTAZIONE
//------------------------------------------------------------------------------

/*!
 * @brief 
	Allocates (with malloc(3)) and returns a new node;
	The member variable [data] is initialized with the value of the parameter
	[data];
	The variable [next] and [prev] are initialized to NULL.
 * @param data 
	The data to create the node with.
 * @return 
	The new node.
 */
t_var	*t_var_new(char	*name, char *value, char type)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (0);
	node->name = name;
	node->value = value;
	node->type = type;
	node->next = 0;
	node->prev = 0;
	return (node);
}

/*!
 * @brief 
	Allocates (with malloc(3)) and returns a new node;
	The member variable [data] is initialized with the value of the parameter
	[data];
	The variable [next] and [prev] are initialized to NULL.
 * @param data 
	The data to create the node with.
 * @return 
	The new node.
 */
t_cmd	*t_cmd_new(char	*token, char type)
{
	t_cmd	*node;

	node = malloc(sizeof(t_cmd));
	if (!node)
		return (0);
	node->token = token;
	node->type = type;
	node->next = 0;
	node->prev = 0;
	return (node);
}

/*!
 * @brief 
	Allocates (with malloc(3)) and returns a new node;
	The member variable [data] is initialized with the value of the parameter
	[data];
	The variable [next] and [prev] are initialized to NULL.
 * @param data 
	The data to create the node with.
 * @return 
	The new node.
 */
t_fd	*t_fd_new(int redirect, int prev_fd, int new_fd)
{
	t_fd	*node;

	node = malloc(sizeof(t_fd));
	if (!node)
		return (0);
	node->redirect = redirect;
	node->prev_fd = prev_fd;
	node->new_fd = new_fd;
	node->next = 0;
	node->prev = 0;
	return (node);
}
