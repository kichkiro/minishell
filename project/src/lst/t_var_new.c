/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 11:01:31 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 22:29:49 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
t_var	*t_var_new(char	*name, char *value)
{
	t_var	*node;

	node = malloc(sizeof(t_var));
	if (!node)
		return (0);
	node->name = name;
	node->value = value;
	node->next = 0;
	node->prev = 0;
	return (node);
}
