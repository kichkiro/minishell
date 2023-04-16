/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_var_n_is_inside.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kichkiro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 16:20:36 by kichkiro          #+#    #+#             */
/*   Updated: 2023/04/16 20:04:19 by kichkiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*!
 * @brief 
	Check if n is in lst.
 * @param lst 
	List of integers.
 * @param n 
	Number to check.
 * @return 
	TRUE if n is in lst.
	FALSE if n is not in lst.
 */
bool	t_var_n_is_inside(t_var *lst, int n)
{
	if (lst)
	{
		while (lst->prev)
			lst = lst->prev;
		while (lst)
		{
			if (lst->data == n)
				return (true);
			lst = lst->next;
		}
	}
	return (false);
}
