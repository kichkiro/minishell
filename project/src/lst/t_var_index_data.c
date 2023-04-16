/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_index_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 16:35:09 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:03:29 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Search data in lst and return its index.
 * @param lst 
	Linked list.
 * @param data 
	Integer.
 * @return 
	An integer corresponding to the index, if not present returns -1.
 */
int	t_var_index_data(t_var *lst, int data)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (lst->data == data)
			return (i);
		lst = lst->next;
		i++;
	}
	return (-1);
}
